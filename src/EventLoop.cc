#include "../Include/EventLoop.h"
#include "../Include/Acceptor.h"
#include "../Include/TcpConnection.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
using std::make_pair;

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtfd(createEventFd())
, _isLooping(false)
, _evtList(1024)
, _acceptor(acceptor)
{
    //将listenfd放在红黑树上进行监听
    //1、listenfd怎么获取
    int listenfd = _acceptor.fd();
    //2、监听函数怎么写addEpollReadFd
    addEpollReadFd(listenfd);
    //3、监听_evtfd
    addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
    close(_evtfd);
}

//事件循环与否对应的两个函数
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    _isLooping = false;
}

//该函数里面封装类epoll_wait函数
void EventLoop::waitEpollFd()
{
    int nready = 0;
    do{
        nready = ::epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    }while(-1 == nready && errno == EINTR);

    if(-1 == nready)
    {
        perror("epoll_wait");
        return;
    }
    else if(0 == nready)
    {
        cout << ">>epoll_wait timeout!!!" << endl;
    }
    else
    {
        //_evtList初始的时候是1024，超过1024就需要进行扩容
        if(nready == (int)_evtList.size())
        {
            _evtList.resize(2 * nready);//手动扩容
        }

        for(int idx = 0; idx < nready; ++idx)
        {
            int fd = _evtList[idx].data.fd;
            //有新的连接请求上来了
            if(fd == _acceptor.fd())
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    //新的连接上来
                    handleNewConnection();
                }
            }
            else if(fd == _evtfd)//满足条件的文件描述符还有_evtfd
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    //阻塞等待
                    handleRead();
                    doPengdingFunctors();//执行所有的回调函数,也就是"任务"
                }
            }
            else //老的连接上有读数据
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    //如果是老的连接,就处理数据的收发
                    handleMessage(fd);
                }
            }
        }
    }
}

//处理新的连接
void EventLoop::handleNewConnection()
{
    //如果connfd结果是正数，就表明三次握手建立
    //成功了，就表明连接是创建了的，也就是可以
    //创建TcpConnection的对象
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }

    //将connfd放在红黑树上进行监听
    addEpollReadFd(connfd);

    //使用该文件描述符connfd创建TcpConnection对象
    TcpConnectionPtr con(new TcpConnection(connfd, this));//堆对象
    
    //连接一旦创建之后，就需要注册相关的三个半事件
    con->setNewConnectionCallback(_onConnection);//连接建立的注册
    con->setMessageCallback(_onMessage);//消息到达的注册
    con->setCloseCallback(_onClose);//连接断开的注册

    //将键值对存放在了map中
    _conns.insert(make_pair(connfd, con));

    //连接建立的事件的时机已经到达，就需要执行回调函数
    con->handleNewConnectionCallback();//连接建立的事件的回调函数的执行
}

//处理老的连接上的数据收发
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        //该连接是存在的
        //连接是存在的，但是连接接收的数据是不是等于0
        //如果等于0，就需要处理连接断开的事件；如果
        //不等于0，那就需要处理数据的收发
        bool flag = it->second->isClosed();//判断是不是断开的标志
        if(flag)
        {
            //连接断开了,连接断开的事件的时机到了
            it->second->handleCloseCallback();//连接断开事件的回调
            //将文件描述符从红黑树上摘除
            delEpollReadFd(fd);
            //以及从map中删除
            _conns.erase(it);
        }
        else
        {
            //连接没有断开，就可以进行正常的数据收发
            //也就是消息达到的事件的时机已经到了
            it->second->handleMessageCallback();//消息到达事件的回调
        }
    }
    else
    {
        cout << "该连接是不存在的"<< endl;
    }
}

//文件描述符的创建
int EventLoop::createEpollFd()
{
    int fd = epoll_create1(0);
    if(fd < 0)
    {
        perror("epoll_create1");
        return -1;
    }
    return fd;
}

//将文件描述符放在红黑树上进行监听
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;//读事件
    evt.data.fd = fd;

    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(ret < 0)
    {
        perror("epoll_ctl add");
        return;
    }
}

//将文件描述符从红黑树上删除
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;//读事件
    evt.data.fd = fd;

    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0)
    {
        perror("epoll_ctl del");
        return;
    }
}

//连接建立的事件的注册
void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onConnection = std::move(cb);
}

//消息到达的事件的注册
void EventLoop::setMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessage = std::move(cb);
}

//连接断开的事件的注册
void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onClose = std::move(cb);
}

//里面封装了write操作，用于通信
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("wakeup");
        return;
    }
}

//创建文件描述符，用于通信
int EventLoop::createEventFd()
{
    int fd = eventfd(10, 0);
    if(fd < 0)
    {
        perror("eventfd");
        return -1;
    }
    return fd;
}
//封装了read函数
void EventLoop::handleRead()
{
    uint64_t two = 0;
    ssize_t ret = read(_evtfd, &two, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("read");
        return;
    }
}

//执行存放在vector中的"任务"
void EventLoop::doPengdingFunctors()
{
    //互斥访问
    //将锁的粒度变小了,并发程度高了
    vector<Functor> tmp;
    {
        MutexLockGuard autoLock(_mutex);
        tmp.swap(_pengdings);
    }
    //遍历vector，将其中的"任务"都执行
    for(auto &cb : tmp)
    {
        //回调执行"任务"，执行发送TcpConnection
        //中的send函数以及发送的数据msg
        cb();
    }
}

//"任务"：要发送给客户端的数据msg以及发送
//数据能力的TcpConnection中的send函数
void EventLoop::runInLoop(Functor &&cb)
{
    //缩短变量的生命周期
    //块作用域
    //锁的范围要小一些(锁的粒度)
    {
        MutexLockGuard autoLock(_mutex);
        _pengdings.push_back(std::move(cb));
    }

    //只要"任务"已经存放在vector<Functor>
    //中，就应该让线程池通知EventLoop进行
    //接收数据，并且将数据发给客户端
    wakeup();
}





