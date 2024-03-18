#include "../Include/TaskQueue.h"
    
TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//任务队列空与满
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

//向任务队列中存数据
void TaskQueue::push(ElemType &&task)
{
    MutexLockGuard autoLock(_mutex);//栈对象

    while(full())
    {
        _notFull.wait();
    }

    _que.push(std::move(task));//移动

    _notEmpty.notify();
}

//从任务队列中取数据
ElemType TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);//栈对象

    while(empty() && _flag)
    {
        _notEmpty.wait();
    }

    if(_flag)
    {
        ElemType tmp = _que.front();
        _que.pop();
        _notFull.notify();

        return tmp;
    }
    else
    {
        return nullptr;
    }
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notifyAll();
}
