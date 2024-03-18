#include "../Include/Thread.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

Thread::Thread(ThreadCallback &&cb)
: _thid(0)
, _isRunning(false)
, _cb(std::move(cb))//注册回调函数
{

}

Thread::~Thread()
{

}

//线程的开始
void Thread::start()
{
    //threadFunc必须是返回类型是void *,参数也是void *
    //现在隐含了一个this指针
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        perror("pthread_create");
        return;
    }

    _isRunning = true;//标识线程已经开始运行了
}

//线程的结束
void Thread::stop()
{
    if(_isRunning)
    {
        int ret = pthread_join(_thid, nullptr);
        if(ret)
        {
            perror("pthread_join");
            return;
        }

        _isRunning = false;//能走到此处，表明线程已经结束了
    }
}

//线程的入口函数
void *Thread::threadFunc(void *arg)
{
    Thread *pth = static_cast<Thread *>(arg);
    if(pth)
    {
        //让线程执行任务
        pth->_cb();//回调函数的执行
    }
    else
    {
        cout << "nullptr == pth" << endl;
    }

    pthread_exit(nullptr);
}
