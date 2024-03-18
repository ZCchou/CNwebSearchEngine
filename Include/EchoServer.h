#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include "TcpConnection.h"
#include "ThreadPool.h"
#include "TcpServer.h"
#include "WebPageSeacher.h"
#include "WordRecommender.h"
class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con,const WebPageSeacher &websearcher,const WordRecommender &wordrecommender);
    void connestablished();
    void process();
    void conclose();
private:
    string _msg;
    TcpConnectionPtr _con;
    WebPageSeacher _websearcher;
    WordRecommender _wordrecommender;
};

class EchoServer
{
public:
    EchoServer(size_t threadNum, size_t queSize
               , const string &ip
               , unsigned short port);
    ~EchoServer();

    //服务器的启动与停止
    void start();
    void stop();
    //三个回调函数
    void onConnection(const TcpConnectionPtr &con);
    void onMessage(const TcpConnectionPtr &con);
    void onClose(const TcpConnectionPtr &con);

private:
    ThreadPool _pool;//线程池对象
    TcpServer _server;//服务器对象
    WebPageSeacher _webseacher;//网页搜索器
    WordRecommender _wordrecommender;//关键词推荐器
};

#endif
