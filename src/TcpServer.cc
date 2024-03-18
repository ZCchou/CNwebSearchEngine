#include "../Include/TcpServer.h"

TcpServer::TcpServer(const string &ip, unsigned short port)
: _acceptor(ip, port)
, _loop(_acceptor)
{

}

TcpServer::~TcpServer()
{

}

//服务器的启动与停止
void TcpServer::start()
{
    _acceptor.ready();//让服务器处于监听状态
    _loop.loop();//让EventLoop循环
}

void TcpServer::stop()
{
    _loop.unloop();
}

//设置回调函数
void TcpServer::setAllCallback(TcpConnectionCallback &&cb1
                               ,TcpConnectionCallback &&cb2
                               ,TcpConnectionCallback &&cb3)
{
    _loop.setNewConnectionCallback(std::move(cb1));
    _loop.setMessageCallback(std::move(cb2));
    _loop.setCloseCallback(std::move(cb3));
}
