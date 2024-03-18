#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;

class Thread
{
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback &&cb);
    ~Thread();

    //线程的开始
    void start();
    //线程的结束
    void stop();

private:
    //线程的入口函数
    static void *threadFunc(void *arg);

private:
    pthread_t _thid;//线程id
    bool _isRunning;//线程是否运行的标志
    ThreadCallback _cb;//执行的回调函数,主要执行的任务
};

#endif
