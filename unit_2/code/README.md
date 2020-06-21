```/*  
     * 函数功能：创建套接字描述符；  
     * 返回值：若成功则返回套接字非负描述符，若出错返回-1；  
     * 函数原型：  
     */   
    #include <sys/socket.h>   
    int socket(int family, int type, int protocol);   
    /*  
     * 说明：  
     * socket类似与open对普通文件操作一样，都是返回描述符，后续的操作都是基于该描述符；  
     * family 表示套接字的通信域，不同的取值决定了socket的地址类型，其一般取值如下：  
     * （1）AF_INET         IPv4因特网域  
     * （2）AF_INET6        IPv6因特网域  
     * （3）AF_UNIX         Unix域  
     * （4）AF_ROUTE        路由套接字  
     * （5）AF_KEY          密钥套接字  
     * （6）AF_UNSPEC       未指定  
     *  
     * type确定socket的类型，常用类型如下：  
     * （1）SOCK_STREAM     有序、可靠、双向的面向连接字节流套接字  
     * （2）SOCK_DGRAM      长度固定的、无连接的不可靠数据报套接字  
     * （3）SOCK_RAW        原始套接字  
     * （4）SOCK_SEQPACKET  长度固定、有序、可靠的面向连接的有序分组套接字  
     *  
     * protocol指定协议，常用取值如下：  
     * （1）0               选择type类型对应的默认协议  
     * （2）IPPROTO_TCP     TCP传输协议  
     * （3）IPPROTO_UDP     UDP传输协议  
     * （4）IPPROTO_SCTP    SCTP传输协议  
     * （5）IPPROTO_TIPC    TIPC传输协议  
     *  
*/   
```
## sockets of protocals
1. TCP
    > socket(AF_INET, SOCK_STREAM, 0)
2. UDP
    > socket(AF_INET, SOCK_DGRAM, 0)
3. Unix Domin
    > socket(AF_UNIX, SOCK_STREAM, 0)

## sock_addr_in  sock_addr
1. blog1
    > https://blog.csdn.net/qingzhuyuxian/article/details/79736821


## UDP
1. blog1
    > https://www.cnblogs.com/developing/articles/10979088.html

```
#include <sys/types.h>
#include <sys/socket.h>
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
              const struct sockaddr *dest_addr, socklen_t addrlen);
第一个参数sockfd:正在监听端口的套接口文件描述符，通过socket获得
第二个参数buf：发送缓冲区，往往是使用者定义的数组，该数组装有要发送的数据
第三个参数len:发送缓冲区的大小，单位是字节
第四个参数flags:填0即可
第五个参数dest_addr:指向接收数据的主机地址信息的结构体，也就是该参数指定数据要发送到哪个主机哪个进程
第六个参数addrlen:表示第五个参数所指向内容的长度
返回值：成功：返回发送成功的数据长度
           失败： -1
```

```
#include <sys/types.h>
#include <sys/socket.h>
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                struct sockaddr *src_addr, socklen_t *addrlen);
第一个参数sockfd:正在监听端口的套接口文件描述符，通过socket获得
第二个参数buf：接收缓冲区，往往是使用者定义的数组，该数组装有接收到的数据
第三个参数len:接收缓冲区的大小，单位是字节
第四个参数flags:填0即可
第五个参数src_addr:指向发送数据的主机地址信息的结构体，也就是我们可以从该参数获取到数据是谁发出的
第六个参数addrlen:表示第五个参数所指向内容的长度
返回值：成功：返回接收成功的数据长度
           失败： -1
```

## bzero(segment fault)
1. if the struct has not been 

## errno 22
1. 
按道理来说，第3个参数是socklen_t的指针，只要声明一个socklen_t的变量len，然后传递地址进去即可，但实际中，我这样做，有时accept就会出现EINVAL的错误，后来查找资料发现，得在accept前将len赋值，即len = sizeof(struct sockaddr),然后再传递&len进去即可。至于为什么如此，我还没想通。先记下来，想通了再更新。

## C doesn't suppot struct "="
1. memcpy: segment fault 
直接声明一个sockaddr_in的指针变量指向结构体指针会出错
memcpy的目的地址必须要有空间，也就是需要malloc
```
    _target_addr=(sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    memcpy(_target_addr,target_addr,sizeof(struct sockaddr_in));
```

## g++ -W,-rpath
1. to find the libxx.so when exe