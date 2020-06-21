#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<iostream>
using namespace std;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

typedef struct node
{
    int _data;
    struct node *_next;
}node_t,*node_p,**node_pp;

node_p head=NULL;

node_p alloc_node(int data){
    node_p ret=(node_p)malloc(sizeof(node_t));
    ret->_data=data;
    ret->_next=NULL;
    return ret;
}

void init(node_pp phead){
    *phead = alloc_node(0);
}

void push_front(node_p head,int data){
    node_p tmp=alloc_node(data);
    tmp->_next=head->_next;
    head->_next=tmp;
}

void pop_front(node_p head,int *pdata){
    if(head->_next!=NULL){
        node_p tmp=head->_next;
        head->_next=tmp->_next;
        *pdata=tmp->_data;
        free(tmp);
    }
}

void show(node_p head){
    node_p cur=head->_next;
    while (cur)
    {
        cout<<cur->_data<<"->";
    }
    cout<<endl;
}

// consumer

void* consumer(void *argv){
    int data;
    while (1)
    {
        pthread_mutex_lock(&lock);
        // if(head->_next==NULL){
        while(head->_next==NULL){
            printf("producer is not ready\n");
            pthread_cond_wait(&cond,&lock);
            //break;
        }
        // }
        // else{
        printf("producer is ready\n");
        pop_front(head,&data);
        printf("%s  data=%d\n",__func__,data);
        // }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

}

void* producer(void *argv){
    int data=rand()%1234;
    while (1)
    {
        sleep(4);
        pthread_mutex_lock(&lock);
        push_front(head,data);
        printf("%s data :: %d\n",__func__,data);
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond);
        
    }
}

int main()
{

    init(&head);
    pthread_t id1,id2;
    pthread_create(&id1,NULL,consumer,NULL);
    pthread_create(&id2,NULL,producer,NULL);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);


    return 0;
}