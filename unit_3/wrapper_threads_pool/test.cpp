#include<iostream>
#include"Threadpool.h"
#include<unistd.h>
#include"Task.h"
using namespace std;
class MyTask:public meihao::Task
{
        public:
                void process()
                {
                        ::srand(time(NULL));
                        int num = ::rand()%100;
                        cout<<"produce a num:"<<num<<endl;
                }
};
int main()
{
        meihao::Threadpool threadpool(4,10);  // 定义一个线程池，里面有4个线程，去处理10个任务
        threadpool.start();
        meihao::Task* ptask = new MyTask();  // 定义一个具体的任务
        int cnt = 10;
        while(cnt--)
        {
                threadpool.addTask(ptask);  // 线程池中添加任务
                sleep(1);
        }
        threadpool.stop();
        return 0;
}