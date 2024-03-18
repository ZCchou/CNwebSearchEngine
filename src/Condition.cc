#include "../Include/Condition.h"
#include "../Include/MutexLock.h"
#include <stdio.h>

Condition::Condition(MutexLock &mutex)
: _mutex(mutex)
{
    //初始化条件变量
    int ret = pthread_cond_init(&_cond, nullptr);
    if(ret)
    {
        perror("pthread_cond_init");
        return;
    }
}

Condition::~Condition()
{
    //销毁条件变量
    int ret = pthread_cond_destroy(&_cond);
    if(ret)
    {
        perror("pthread_cond_destroy");
        return;
    }
}

//等待函数
void Condition::wait()
{
    int ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
    if(ret)
    {
        perror("pthread_cond_init");
        return;
    }
}

//发通知
void Condition::notify()
{
    int ret = pthread_cond_signal(&_cond);
    if(ret)
    {
        perror("pthread_cond_signal");
        return;
    }
}

void Condition::notifyAll()
{
    int ret = pthread_cond_broadcast(&_cond);
    if(ret)
    {
        perror("pthread_cond_broadcast");
        return;
    }
}
