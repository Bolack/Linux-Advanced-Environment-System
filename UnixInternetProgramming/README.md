# Unix Internet Programming

## EPOLL
1. 最前面的三个文件描述符（0，1，2）分别与标准输入（stdin），标准输出（stdout）和标准错误（stderr）对应。
2. //水平触发
ret = read(fd, buf, sizeof(buf));

//边缘触发
while(true) {
    ret = read(fd, buf, sizeof(buf);
    if (ret == EAGAIN) break;
}
## file tree

## Makefile
1. $@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件

## TCP

### 1. two port:   
    port 8020 and port 8021
    one charges for controling and the other charges for transporting
    
### linux nc
    test network
``` 
    语　　法：nc [-hlnruz][-g<网关...>][-G<指向器数目>][-i<延迟秒数>][-o<输出文件>][-p<通信端口>]
		  [-s<来源位址>][-v...][-w<超时秒数>][主机名称][通信端口...]
    参　　数：
    -g<网关>         设置路由器跃程通信网关，最多可设置8个。
    -G<指向器数目>   设置来源路由指向器，其数值为4的倍数。
    -h               在线帮助。
    -i<延迟秒数>     设置时间间隔，以便传送信息及扫描通信端口。
    -l               监听模式，用于入站连接 (监听本地端口)。
    -n               直接使用IP地址，而不通过域名服务器。
    -o<输出文件>     指定文件名称，把往来传输的数据以16进制字码倾倒成该文件保存。
    -p<通信端口>     设置本地主机使用的通信端口。
    -r               随机指定本地与远端主机的通信端口。
    -s<来源位址>     设置本地主机送出数据包的IP地址。
    -u               使用UDP传输协议。
    -v               显示指令执行过程。
    -w<超时秒数>     设置等待连线的时间。
    -z               使用0输入/输出模式，只在扫描通信端口时使
```

### 非阻塞IO
1. 阻塞式IO 0为标准输入；1为标准输出；如果读不到则阻塞
```    
while ((size=read(0,buf,1024))!=0)
    {
        writesize=write(1,buf,size);
        printf("write in %d byte %d\n",writesize,errno);
    }
```
2.非阻塞式IO 
```
int flags=fcntl(0,F_GETFL,0);
flags|=O_NONBLOCK;
fcntl(0,F_SETFL,flags);
while ((size=read(0,buf,1024))!=0)
    {
        writesize=write(1,buf,size);
        printf("write in %d byte errno %d\n",writesize,errno);
    }
```
### ET
> 参考博客 https://www.zhihu.com/question/263931629/answer/1012125255
```
    while(1){
        int nfds=epoll_wait(epollfd,events,20,500);
        for(int i=0;i<nfds;i++){
            if ((events[i].data.fd==0)&&(events[i].events & EPOLLIN)) 
            {
                bzero(buf,sizeof(buf));
                read(0,buf,4);//从标准输入读取4个字符
                printf("%s\n",buf);
                printf("0 errno:%d\n",errno);
                epoll_ctl(epollfd,EPOLL_CTL_MOD,1,&eventout);
            }
}

```
1.读 LT  水平触发
```
eventin.events=EPOLLIN;
```
> wangmin@wangmin:~/UnixInternetProgramming/UnixInternetProgramming/practice/epoll_ET_LE$ ./local_file_rw   
123456789  
12340 errno:0  
56780 errno:0  
9  
0 errno:0  

2.读 ET 边沿触发
```
eventin.events=EPOLLIN | EPOLLET;
```
> wangmin@wangmin:~/UnixInternetProgramming/UnixInternetProgramming/practice/epoll_ET_LE$ ./local_file_rw 
123456789  
1234errno:0  
123  
5678errno:0 //输出错误 可见边沿触发需要特殊处理 

3. 写 LT 水平触发
>     eventin.events=EPOLLIN | EPOLLET;
    // eventin.events=EPOLLIN;
    eventin.data.fd=0;//stand input
    // eventout.events=EPOLLOUT|EPOLLET;
    eventout.events=EPOLLOUT;
``` 
    while(1){
        int nfds=epoll_wait(epollfd,events,20,500);
        for(int i=0;i<nfds;i++){
            if ((events[i].data.fd==0)&&(events[i].events & EPOLLIN)) 
            {
                bzero(buf,sizeof(buf));
                read(0,buf,4);
                printf("%s",buf);
                printf("errno:%d\n",errno);
                epoll_ctl(epollfd,EPOLL_CTL_MOD,1,&eventout);
            }
            else if((events[i].data.fd==1)&&(events[i].events & EPOLLOUT)){
                write(1,buf,1024);
                bzero(buf,sizeof(buf));
                printf("1 errno:%d\n",errno);
                // epoll_ctl(epollfd,EPOLL_CTL_MOD,1,&eventin);
            }
        }
    }
```
> 持续输出 1 errno0//表示一直可写（写缓冲区没有数据）
> 边沿触发 写缓冲区状态改变才触发

> 需要调用非阻塞IO来处理，否则会被阻塞

```
.
├── 大作业
│   ├── ~$大作业.pptx
│   ├── (9条消息)Linux epoll模型详解及源码分析_运维_我心依旧，明月长歌-CSDN博客.pdf
│   ├── 大作业.pptx
│   ├── 互联网程序设计实验报告.doc
│   ├── 王敏-201922080602
│   │   ├── 互联网程序设计实验报告.doc
│   │   └── server
│   ├── Proactor.pdf
│   ├── reactor-siemens.pdf
│   ├── server
│   │   ├── epollServer
│   │   ├── epollServer.cpp
│   │   ├── hello.txt
│   │   ├── Makefile
│   │   ├── pic.jpg
│   │   └── uploadfile.txt
│   ├── UNIX网络编程卷1：套接字联网API（第3版）.pdf
│   └── unpv13e.tar.gz
├── 课件
│   ├── 第0章.pptx
│   ├── 第10章.pptx
│   ├── 第1章.pptx
│   ├── 第2章.pptx
│   ├── 第3章.pptx
│   ├── 第4章.pptx
│   ├── 第5章.pptx
│   ├── 第6章.pptx
│   ├── 第7章.pptx
│   ├── 第8章.pptx
│   └── 第9章.pptx
├── practice
│   ├── epoll-demo
│   │   ├── epollClient
│   │   ├── epollClient.c
│   │   ├── epollServer
│   │   ├── epollServer.c
│   │   ├── Makefile
│   │   └── README.md
│   ├── epoll_ET_LE
│   │   ├── epoll_local_file_rw.cpp
│   │   ├── local_file_rw
│   │   ├── local_file_rw.cpp
│   │   ├── main
│   │   ├── main.cpp
│   │   ├── Makefile
│   │   ├── pic_copy.jpg
│   │   ├── pic.jpg
│   │   └── test.txt
│   ├── epoll_local_demo
│   │   ├── epolldemo
│   │   ├── epolldemo.c
│   │   └── Makefile
│   ├── file_wr_practice
│   │   ├── filecpy
│   │   ├── filecpy.c
│   │   ├── hello
│   │   ├── hello.c
│   │   ├── hello copy
│   │   ├── hellorewrite
│   │   ├── hellorewrite.c
│   │   ├── ls
│   │   ├── ls.c
│   │   ├── Makefile
│   │   ├── piccopy.jpg
│   │   └── pic.jpg
│   ├── none_blocks
│   │   ├── main
│   │   ├── main.cpp
│   │   ├── Makefile
│   │   └── pic_copy.jpg
│   └── select_practice
│       ├── Makefile
│       ├── select_prac
│       └── select_prac.c
├── README.md

```