#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "NonCopyable.h"
#include <pthread.h>

class MutexLock;//前向声明,建议

class Condition
: NonCopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    //等待函数
    void wait();
    //发通知
    void notify();
    void notifyAll();

private:
    MutexLock &_mutex;//互斥锁的引用
    pthread_cond_t _cond;//条件变量

};

#endif
