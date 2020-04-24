#include <sys/epoll.h>
#include <stdio.h>

#define ET_ON 1
#define STAND_IN 0
#define STAND_OUT 1

static void add_event(int epollfd, int fd, int state, int et_on)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if (et_on)
        ev.events = state| EPOLLET; // Edge Triger
    else
        ev.events = state;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void main()
{
    char buf[12];
    int ret;
    struct epoll_event events[20];
    int epollfd = epoll_create(20);
    add_event(epollfd, STAND_IN, EPOLLIN, ET_ON); 
    while (1)
    {
        ret = epoll_wait(epollfd, events, 20, -1);
        int fd;
        for (int i = 0; i < ret; i++)
        {
            fd = events[i].data.fd;
            if(events[i].events & EPOLLIN){
                printf("Triggering\n");
                scanf("%s",buf);
            }      
            printf("%s",buf);
        }
    }
}
