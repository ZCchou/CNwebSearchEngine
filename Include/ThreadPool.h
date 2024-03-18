#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <memory>
#include <functional>

using std::vector;
using std::unique_ptr;
using std::function;

class Thread;//前向声明

using Task = function<void()>;

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    //线程池的启动与停止
    void start();
    void stop();

    //添加任务
    void addTask(Task &&task);
private:
    //获取任务
    Task getTask();

    //线程池交给工作线程做的事件
    void doTask();

private:
    size_t _threadNum;//子线程的数目
    size_t _queSize;//任务队列的大小
    vector<unique_ptr<Thread>> _threads;//存放所有子线程（工作线程）的容器
    TaskQueue _taskQue;//存放任务的数据结构（其实就是封装的类）
    bool _isExit;//标识线程池是否退出的标志
};

#endif
