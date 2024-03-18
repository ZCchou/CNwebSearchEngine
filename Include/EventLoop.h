#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include "MutexLock.h"
#include <sys/epoll.h>
#include <vector>
#include <functional>
#include <map>
#include <memory>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

class Acceptor;//前向声明
class TcpConnection;//前向声明

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback  = function<void(const TcpConnectionPtr &con)>;
using Functor = function<void()>;

class EventLoop
{
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    //事件循环与否对应的两个函数
    void loop();
    void unloop();
private:
    //该函数里面封装类epoll_wait函数
    void waitEpollFd();

    //处理新的连接
    void handleNewConnection();

    //处理老的连接上的数据收发
    void handleMessage(int fd);

    //文件描述符的创建
    int createEpollFd();

    //将文件描述符放在红黑树上进行监听
    void addEpollReadFd(int fd);

    //将文件描述符从红黑树上删除
    void delEpollReadFd(int fd);

public:
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);

public:
    //里面封装了write操作，用于通信
    void wakeup();
private:
    //创建文件描述符，用于通信
    int createEventFd();
    //封装了read函数
    void handleRead();
    //执行存放在vector中的"任务"
    void doPengdingFunctors();

public:
    void runInLoop(Functor &&cb);

private:
    int _epfd;//epoll_create创建的红黑树关联结点
    int _evtfd;//eventfd创建的用于通信的文件描述符
    bool _isLooping;//标识循环是否在运行的标志
    vector<struct epoll_event> _evtList;//存放满足条件文件描述符的结构体
    Acceptor &_acceptor;//需要调用该类的成员函数accept
    map<int, TcpConnectionPtr> _conns;//存放文件描述符与TcpConnection的键值对

    TcpConnectionCallback _onConnection;//连接建立
    TcpConnectionCallback _onMessage;//文件描述符可读，也就是数据的收发
    TcpConnectionCallback _onClose;//连接断开

    vector<Functor> _pengdings;//待执行的"任务"
    MutexLock _mutex;//互斥锁，互斥访问vector（线程池与EventLoop互斥访问）
};

#endif
