#ifndef __THREADPOOLTHREAD_H__
#define __THREADPOOLTHREAD_H__
#include<iostream>
#include"Thread.h"
#include"Threadpool.h"
using namespace std;
namespace meihao
{
        class Threadpoolthread:public Thread
        {
                public:
                Threadpoolthread(Threadpool& threadpool):_threadpool(threadpool){}
                void run()
                {
                        _threadpool.threadFunc();  // 继承的线程池线程内部实现的线程执行体方法
                        // 调用线程池的threadFunc方法，线程池的所有线程都去执行这个方法
                }
                private:
                        Threadpool& _threadpool;
        };
};
#endif