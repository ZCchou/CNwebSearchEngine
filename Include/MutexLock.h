#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include "NonCopyable.h"
#include <pthread.h>

class MutexLock
: NonCopyable
{
public:
    MutexLock();
    ~MutexLock();

    //上锁
    void lock();
    //尝试上锁
    void tryLock();
    //解锁
    void unlock();
    //获取数据成员
    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;//互斥锁的变量
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {
        //在构造函数中加锁
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        //在析构函数中释放锁
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;
};

#endif
