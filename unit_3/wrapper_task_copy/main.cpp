// #include<pthread.h>
// #include<iostream>
// using namespace std;


// class Task{
//     private:
//         void* (*_func)(void *argv);
//         void* _argv;
//     public:
//         int set_fuc(void*(*func)(void *),void* argv);
//         void* run();
//         void get_func(void*(*func)(void *));
//         void* get_argv();
// };

// int Task::set_fuc(void*(*func)(void *),void* argv){
//     this->_func=func;
//     this->_argv=argv;
//     return 1;
// }

// void* Task::run(){
//     void* re=(void*)(*_func)(_argv);
//     return re;
// }

// void Task::get_func(void*(*func)(void *)){
//     func=this->_func;
// }

// void* Task::get_argv(){
//     return this->_argv;
// }

// class Thread{
//     private:
//         pthread_t id_;
//         Task *task_;
//     public:
//         Thread();
//         void set_task(Task *task);
//         int start();
//         void** join();
//         pthread_t get_id();

// };

// Thread::Thread(){

// };

// void Thread::set_task(Task *task){
//     this->task_=task_;
// }

// int Thread::start(){
//     void*(*func)(void *argv);
//     return pthread_create(&this->id_,NULL,func,this->task_->get_argv());
// }

// void** Thread::join(){
//     void** ret;
//     pthread_join(this->id_,ret);
//     return ret;
// }


typedef struct arg_add
{
    int a,b;
    /* data */
}ARG_ADD;

// void* add(void *argv){
//     ARG_ADD *args=(ARG_ADD*)argv;
//     int sum=args->a+args->b;
//     cout<<"sum = "<<sum<<endl;
//     int* sum_p;
//     sum_p=&sum;
//     // return (void*)&sum;
//     return sum_p; 
// }


int main(){
    ARG_ADD *arg;// =(ARG_ADD*)malloc(sizeof(ARG_ADD));
    arg->b=2;
    arg->a=1;
    // Thread t1,t2;
    // Task *task;
    // task->set_fuc(add,arg);
    // // char *ret =(char*)task.run();
    // t1.set_task(task);
    // t1.start();
    // void **ret = t1.join();
    // // printf("%s\n",ret);
    // cout<<"return *ret ="<<*ret<< endl;
    // cout<<"return (int*)*ret = "<<(int*)*ret<<endl;
    // return 1;
    
}