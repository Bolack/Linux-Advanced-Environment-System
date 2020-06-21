#include "epoll_class.h"
using namespace std;

MyEpoll::MyEpoll(int size,int timeout,int epoll_events) : _size(size), _timeout(timeout), _epoll_events(epoll_events)
{
    _epoll_fd = epoll_create(_size);
}

int MyEpoll::_ctl(int fd, int op, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    return epoll_ctl(_epoll_fd, op, fd, &ev);
}

int MyEpoll::add_event(int fd, int state)
{
    return _ctl(fd, EPOLL_CTL_ADD, state);
}

int MyEpoll::mod_event(int fd, int state)
{
    return _ctl(fd, EPOLL_CTL_MOD, state);
}

int MyEpoll::del_event(int fd, int state)
{
    return _ctl(fd, EPOLL_CTL_DEL, state);
}

int MyEpoll::wait(struct epoll_event *events)
{
    return epoll_wait(_epoll_fd, events, _epoll_events, _timeout);
}

void MyEpoll::close()
{
    ::close(_epoll_fd);
}

int MyEpoll::get_epoll_fd(){
    return _epoll_fd;
}