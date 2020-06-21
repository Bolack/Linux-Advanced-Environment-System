#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

const int EPOLLEVENTS = 100;
const int FDSIZE = 1000;

class MyEpoll
{
private:
    int _epoll_fd; //epoll handle
    int _size;     // the number of fd to listeb
    int _epoll_events;
    struct epoll_event _ev;
    int _timeout;
    int _ctl(int fd, int op, int state);
protected:
    int fd_;
public:
    MyEpoll(int size,int timeout,int epoll_events);
    int wait(struct epoll_event *__event); // return the number of events
    int add_event(int fd, int state);
    int mod_event(int fd, int state);
    int del_event(int fd, int state);
    int get_epoll_fd();
    void close();
    struct epoll_event events_[EPOLLEVENTS];
    // void virtual handle_events(int fd, int ret,struct epoll_event *events) = 0;
};