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
    // return (void*)&sum;
    return sum_p; 
}

int main(){
    void* (*func)(void *argv);
    ARG_ADD argv;
    argv.a=1;
    argv.b=2;
    func=add;
    int *ret =(int*)(*func)((void*)&argv);
    cout<<"return "<<*ret<< endl;
    return 1;
}