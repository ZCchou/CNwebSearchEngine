#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"

class TcpServer
{
public:
    TcpServer(const string &ip, unsigned short port);
    ~TcpServer();

    //服务器的启动与停止
    void start();
    void stop();
    //设置回调函数
    void setAllCallback(TcpConnectionCallback &&cb1, 
                        TcpConnectionCallback &&cb2,
                        TcpConnectionCallback &&cb3);

private:
    Acceptor _acceptor;//链接器类
    EventLoop _loop;//事件循环类

};

#endif
