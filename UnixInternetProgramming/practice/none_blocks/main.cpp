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
    /* set no block */
    int flags = fcntl(0, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);
    flags = fcntl(1, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(1, F_SETFL, flags);
    int size;
    int writesize;
    /* set non-block IO*/
    while ((size=read(0,buf,4))>=0)
    {
        printf("write in %d byte errno %d\n",size,errno);
        writesize=write(1,buf,size);
                                                                                                  
    }
    printf("Success!\n");
    printf("write in %d byte errno %d\n",size,errno);
    return 0;
}
