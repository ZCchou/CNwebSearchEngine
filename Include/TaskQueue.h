#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

using std::queue;
using std::function;

using ElemType = function<void()>;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //任务队列空与满
    bool empty() const;
    bool full() const;

    //向任务队列中存数据
    void push(ElemType &&task);
    //从任务队列中取数据
    ElemType pop();

    //唤醒_notEmpty条件变量上的线程
    void wakeup();

private:
    size_t _queSize;//任务队列的大小
    queue<ElemType> _que;//存放数据的数据结构
    MutexLock _mutex;//互斥锁
    Condition _notEmpty;//非空条件变量
    Condition _notFull;//非满条件变量
    bool _flag;//标志位
};

#endif
