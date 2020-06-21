#ifndef __TASK_H__
#define __TASK_H__
#include<iostream>
using namespace std;
namespace meihao
{
        class Task
        {
                public:
                        virtual void process() = 0;  // 线程池里面的线程具体要做的任务
        };
};
#endif
