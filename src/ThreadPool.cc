#include "../Include/ThreadPool.h"
#include "../Include/Thread.h"
#include <unistd.h>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{
    //使用的是预留空间
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool()
{

}

//线程池的启动与停止
void ThreadPool::start()
{
    for(size_t idx = 0; idx < _threadNum; ++idx)
    {
        //线程池交给工作线程所做的任务就是doTask,需要将doTask绑定到Thread
        //类中，交给数据成员ThreadCallback _cb
        unique_ptr<Thread> up(new Thread(bind(&ThreadPool::doTask, this)));

        //2、将所有的工作线程放在vector存起来
        _threads.push_back(std::move(up));
    }

    //3、遍历vector，将所有的工作线程运行起来
    for(auto &th : _threads)
    {
        th->start();//将所有的工作线程运行起来
    }
}

void ThreadPool::stop()
{
    //只要任务队列中有任务，就不能让工作线程退出
    while(!_taskQue.empty())
    {
        sleep(1);
    }
    _isExit = true;//标识线程池的退出

    //唤醒所有在_notEmpty条件变量上的线程
    _taskQue.wakeup();

    //遍历vector，将所有的工作线程停止运行
    for(auto &th : _threads)
    {
        th->stop();//将所有的工作线程停止运行
    }
}

//添加任务
void ThreadPool::addTask(Task &&task)
{
    if(task)
    {
        _taskQue.push(std::move(task));
    }
}

//获取任务
Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

void ThreadPool::doTask()
{
    //只要线程池不退出，那就应该让工作线程一直执行任务
    while(!_isExit)
    {
        //1、首先要获取任务
        Task taskcb = getTask();
        if(taskcb)
        {
            //2、其次再执行任务
            taskcb();//执行回调函数
        }
        else
        {
            cout << "nullptr == ptask" << endl;
        }
    }
}
