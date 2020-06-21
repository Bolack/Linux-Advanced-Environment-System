#include<stdio.h>
#include<pthread.h>
#include<iostream>
using namespace std;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
int g_val=0;

void* add(void *argv){
    for(int i=0;i<5000;++i){
        pthread_mutex_lock(&lock);
        int tmp=g_val;
        g_val=tmp+1;
        for(int j=0;j<10000;j++){// add the run time

        }
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_t id1,id2;
    pthread_create(&id1,NULL,add,NULL);
    pthread_create(&id2,NULL,add,NULL);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    cout<<"gval: "<<g_val<<endl;

    return 0;
}