#include<iostream>
using namespace std;

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
    char* str="abc";
    // return (void*)&sum;
    return str; 
}

class Task{
    private:
        void* (*_func)(void *argv);
        void* argv;
    public:
        int set_fuc(void*(*func)(void *),void* argv);
        void* run();
};

int Task::set_fuc(void*(*func)(void *),void* argv){
    this->_func=func;
    this->argv=argv;
    return 1;
}

void* Task::run(){
    void* re=(void*)(*_func)(argv);
    return re;
}


int main(){
    // void* (*func)(void *argv);
    ARG_ADD* argv;
    argv->a=1;
    argv->b=2;
    Task task;
    task.set_fuc(add,argv);
    char *ret =(char*)task.run();
    printf("%s\n",ret);
    cout<<"return "<<*ret<< endl;
    return 1;
}