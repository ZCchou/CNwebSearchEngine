#include "../Include/TcpConnection.h"
#include "../Include/EventLoop.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd, EventLoop *loop)
: _loop(loop)
, _sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string &msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

//这个函数怎么实现呢？
//参数中的msg是线程池处理好之后的数据，是可以直接
//发给客户端的数据，也就是经过业务逻辑处理之后的
//可以直接发送给客户端的数据
//数据处理好之后，需要交给EventLoop，那即使将数据
//交给了EventLoop，但是EventLoop是没有发送数据的
//能力的,所以除了将msg发送给EventLoop之外，还要
//将发送数据的能力的TcpConnection交给EventLoop
//而在TcpConnection发送数据能力的也就是函数
//send，最终我们可以推导出来的是：
//将msg以及TcpConnection中的send函数打包发给EventLoop
//一直在EventLoop中所说的"任务"，其实就是要发送
//的数据msg以及发生数据能力的TcpConnection以及
//其中的函数send
void TcpConnection::sendInLoop(const string &msg)
{
    if(_loop)
    {
        //在EventLoop中需要添加函数runInLoop
        //void(function<void>())
        _loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
    }
}
string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readLine(buff, sizeof(buff));

    return string(buff);
}

bool TcpConnection::isClosed() const
{
    //如何判断是不是断开呢
    char buf[20] = {0};
    //MSG_PEEK只会将数据拷贝出来，并不会从内核缓冲区中删除
    int ret = ::recv(_sock.fd(), buf, sizeof(buf), MSG_PEEK);

    return (0 == ret);
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }

    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
    }

    return InetAddress(addr);
}

//三个回调函数的注册
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &cb)
{
    _onConnection = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onMessage = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onClose = cb;
}

//三个回调函数的执行
void TcpConnection::handleNewConnectionCallback()
{
    if(_onConnection)
    {
        //有可能会发生智能指针的误用
        /* _onConnection(shared_ptr<TcpConnection>(this)); */
        _onConnection(shared_from_this());
    }
    else
    {
        cout << "handleNewConnection == nullptr" << endl;
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage)
    {
        /* _onMessage(shared_ptr<TcpConnection>(this)); */
        _onMessage(shared_from_this());
    }
    else
    {
        cout << "handleMessageCallback == nullptr" << endl;
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        /* _onClose(shared_ptr<TcpConnection>(this)); */
        _onClose(shared_from_this());
    }
    else
    {
        cout << "handleCloseCallback == nullptr" << endl;
    }
}
