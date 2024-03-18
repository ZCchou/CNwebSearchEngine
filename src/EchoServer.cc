#include "../Include/EchoServer.h"

using std::cout;
using std::endl;
using std::bind;

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con,const WebPageSeacher &websearcher,const WordRecommender &wordrecommender)
: _msg(msg)
, _con(con)
,_websearcher(websearcher)
,_wordrecommender(wordrecommender)
{

}

void MyTask::process()
{

    string outcome;
    int protol;
    string wtd=_msg;
    //删除消息的第1个数字
    size_t pos=wtd.find_first_not_of("12");
    if (pos!=std::string::npos){wtd=wtd.substr(pos);}
    else{wtd="";}
    string rwtd=wtd;
    rwtd.erase(std::remove_if(rwtd.begin(), rwtd.end(), ::isspace), rwtd.end());
    istringstream iss(_msg);
    iss>>protol;
switch(protol){
    //协议1是关键字推荐
    //协议2是网页搜索
case 1:{
 outcome =_wordrecommender.recommend(rwtd);
 break;    
       }
case 2:{
 outcome= _websearcher.doQuery(wtd);
break;
       }
default:
       {
 outcome= "无效输入\n";
       break;
       }
            }
    _con->sendInLoop(outcome+"\n已响应,输入1+单字/词获得推荐词，输入2+空格分开的词获得文章\n");
}

EchoServer::EchoServer(size_t threadNum, size_t queSize
                       , const string &ip
                       , unsigned short port)
: _pool(threadNum, queSize)
, _server(ip, port)
{
}

EchoServer::~EchoServer()
{

}

//服务器的启动与停止
void EchoServer::start()
{
    _pool.start();//让线程池启动

    using namespace std::placeholders;
    //void(EchoServer *, const TcpConnectionPtr &)
    //void(const TcpConnectionPtr &)
    _server.setAllCallback(bind(&EchoServer::onConnection, this, _1)
                           , bind(&EchoServer::onMessage, this, _1)
                           , bind(&EchoServer::onClose, this, _1));

    _server.start();//让EventLoop启动
}

void EchoServer::stop()
{
    _pool.stop();
    _server.stop();
}

//三个回调函数
void EchoServer::onConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!" << endl; 
    con->sendInLoop("连接到服务器，输入1+单字/词获得推荐词，输入2+空格分开的词获得文章\n");
}

void EchoServer::onMessage(const TcpConnectionPtr &con)
{
    //接收客户端的数据
    string msg = con->receive();//读网络数据,Read,Input
    cout << ">>recv msg from client : " << msg << endl;

    MyTask task(msg, con,_webseacher,_wordrecommender);
    _pool.addTask(std::bind(&MyTask::process, task));
    con->sendInLoop("\n");
}

void EchoServer::onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl; 
}
