#include "../Include/MutexLock.h"
#include <stdio.h>

MutexLock::MutexLock()
{
    //在构造函数中初始化互斥锁
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if(ret)
    {
        perror("pthread_mutex_init");
        return;
    }
}

MutexLock::~MutexLock()
{
    //析构函数中释放互斥锁
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_destroy");
        return;
    }
}

//上锁
void MutexLock::lock()
{
    int ret = pthread_mutex_lock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_lock");
        return;
    }
}

//尝试上锁
void MutexLock::tryLock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_trylock");
        return;
    }
}

//解锁
void MutexLock::unlock()
{
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_unlock");
        return;
    }
}

//获取数据成员
pthread_mutex_t *MutexLock::getMutexLockPtr()
{
    return &_mutex;
}





