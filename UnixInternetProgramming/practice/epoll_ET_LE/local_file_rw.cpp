/** 
 * 验证epoll的LT与ET模式的区别, epoll_server.cpp
 * zhangyl 2019.04.01
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <poll.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>
//添加事件
static void add_event(int epollfd, int fd, int state);
//修改事件
static void modify_event(int epollfd, int fd, int state);
//删除事件
static void delete_event(int epollfd, int fd, int state);

#define TEMPBUF 8

int main()
{
    int epollfd = epoll_create(20);
    int fd_in = open("pic.jpg", O_RDONLY);
    int fd_out = open("pic_copy.jpg", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    char buf[1024];
    bzero(buf, sizeof(buf));
    int size;
    int writesize;
    epollfd = epoll_create(20);
    struct epoll_event eventin;
    struct epoll_event eventout;
    struct epoll_event events[20];
    // eventin.events = EPOLLIN | EPOLLET;
    eventin.events=EPOLLIN;
    eventin.data.fd = 0; //stand input
    epoll_ctl(epollfd, EPOLL_CTL_ADD, 0, &eventin);
    /* set no block */
    int flags = fcntl(0, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);
    flags = fcntl(1, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(1, F_SETFL, flags);

    // eventout.events=EPOLLOUT;
    eventout.events=EPOLLOUT|EPOLLET;
    eventout.data.fd=1;// stand out
    epoll_ctl(epollfd,EPOLL_CTL_ADD,1,&eventout);
    /* set non-block IO*/
    // int flags=fcntl(0,F_GETFL,0);// get standin flags
    // flags|=O_NONBLOCK;
    // fcntl(0,F_SETFL,flags);
    // printf("sss");
    while (1)
    {
        int nfds = epoll_wait(epollfd, events, 20, 500);
        for (int i = 0; i < nfds; i++)
        {
            if ((events[i].data.fd == 0) && (events[i].events & EPOLLIN))
            {
                bzero(buf, sizeof(buf));
                int ret;
                char tempbuf[4];
                bzero(buf, 4);
                // printf("0 read errno:%d\n",errno);
                // read all date onetime
                while ((ret = read(0, tempbuf, 4)) > 0)
                {
                    strncat(buf, tempbuf, ret);
                }
                //read a part of data
                // read(0, tempbuf, 4);
                printf("0 read errno:%d\n", errno);
            }
            else if ((events[i].data.fd == 1) && (events[i].events & EPOLLOUT))
            {
                // printf("1 write %d; errno:%d\n",errno,errno);
                int ret = 0;
                while (buf[i] != '\0')
                {
                    write(1, buf + i, 1);
                    i += 1;
                }
                // eventout.events = EPOLLOUT | EPOLLET;
                // // eventout.events=EPOLLOUT;
                // eventout.data.fd = 1; // stand out
                // epoll_ctl(epollfd, EPOLL_CTL_DEL, 20, &eventout);
                bzero(buf, 1024);
                // ret=write(1,buf,4);
                // int ret=1;
                // printf("1 write %d; errno:%d\n", ret, errno);
                // epoll_ctl(epollfd,EPOLL_CTL_MOD,1,&eventin);
                // epoll_ctl(epollfd,EPOLL_CTL_ADD,20,&eventout);
                // sleep(5);
                /*register client*/
                // eventout.events=EPOLLOUT;
                // eventin.events = EPOLLOUT | EPOLLET;
                // eventin.data.fd = 1; // stand out
                // epoll_ctl(epollfd, EPOLL_CTL_MOD, 20, &eventin);
            }
        }
    }
    // /* set non-block IO*/
    // int flags=fcntl(0,F_GETFL,0);
    // flags|=O_NONBLOCK;
    // fcntl(0,F_SETFL,flags);
    // while ((size=read(0,buf,1024))!=0)
    // {
    //     writesize=write(1,buf,size);
    //     // printf("write in %d byte errno %d\n",writesize,errno);
    // }
    // printf("Success!\n");
    return 0;
}

static void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}