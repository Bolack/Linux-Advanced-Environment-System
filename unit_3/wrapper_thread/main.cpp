#include<pthread.h>
#include<iostream>
using namespace std;

typedef void*(*func)(void*);

class Task{
    private:
        void* (*_func)(void *argv);
        void* _argv;
    public:
        int set_fuc(void*(*func)(void *),void* argv);
        void* run();
        func get_func();
        void* get_argv();
};

int Task::set_fuc(void*(*func)(void *),void* argv){
    this->_func=func;
    this->_argv=argv;
    return 1;
}

void* Task::run(){
    void* re=(void*)(*_func)(_argv);
    return re;
}

func Task::get_func(){
    return _func;
}

void* Task::get_argv(){
    return this->_argv;
}

class Thread{
    private:
        pthread_t id_;
        Task *task_;
    public:
        Thread();
        void set_task(Task *task);
        int start();
        void** join();
        pthread_t get_id();

};

Thread::Thread(){

};

void Thread::set_task(Task *task){
    task_=(Task*)malloc(sizeof(Task));
    this->task_=task;
}

int Thread::start(){
    void*(*func)(void *argv);
    func=this->task_->get_func();
    return pthread_create(&id_,NULL,func,task_->get_argv());
}

void** Thread::join(){
    void** retp;
    void* ret;
    pthread_join(this->id_,&ret);
    retp=&ret;
    return retp;
}


typedef struct arg_add
{
    int a,b;
    /* data */
}ARG_ADD;

void* add(void *argv){
    ARG_ADD *args=(ARG_ADD*)argv;
    int sum=args->a+args->b;
    cout<<"sum = "<<sum<<endl;
    int* sum_p;
    sum_p=&sum;
    // return (void*)&sum;
    return sum_p; 
}


int main(){
    ARG_ADD *arg =(ARG_ADD*)malloc(sizeof(ARG_ADD));
    arg->b=2;
    arg->a=1;
    Thread t1,t2;
    Task task;
    task.set_fuc(add,arg);
    // char *ret =(char*)task.run();
    Task *taskp=&task;
    t1.set_task(taskp);
    t1.start();
    int *ret = (int*)malloc(sizeof(int));
    void ** retp;
    retp = t1.join();
    ret=(int*)*retp;
    // printf("%s\n",ret);
    cout<<"return *ret ="<<*ret<< endl;
    cout<<"return (int*)*ret = "<<(int*)*ret<<endl;
    return 1;
    
}