


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <netinet/in.h> // for sockaddr_in
#include <arpa/inet.h>

#ifndef _SOCKETS_H_
#define _SOCKETS_H_
/*
## sockets of protocals
1. TCP
    > socket(AF_INET, SOCK_STREAM, 0)
2. UDP
    > socket(AF_INET, SOCK_DGRAM, 0)
3. Unix Domin
    > socket(AF_UNIX, SOCK_STREAM, 0)
*/

using namespace std;

#define BUFFSIZE 1024

class Socket
{
private:
    map<string, int> socket_domin;
    map<string, int> socket_type;
    int _set_bind_sockaddr(char* ip, int port);
public:
    int creat();
    // int connect();
    // int listen();
    int send(string message);
    string recive();
    bool bind(char* ip, int port); // for server
    void close(){
        ::close(_socket);
    }
    void set_source_addr(sockaddr_in *source_addr);
    void get_source_addr(struct sockaddr_in *source_addr);

protected:
    int _socket; // can be use by sub class
    struct sockaddr _bind_sockaddr;
    string _protocal;
    struct sockaddr_in *_source_addr;
};

/*UDP*/
class UdpSocket:public Socket
{   

    public:
        UdpSocket();
        int send(string message);
        string recive();
        void set_target_addr(char* ip,int port); 
        void set_target_addr(sockaddr_in *target_addr); 
    protected:
        struct sockaddr_in *_target_addr;
};

class UdpClientSocket:public UdpSocket
{
    
};

class UdpServerSocket:public UdpSocket
{
    
};

/*TCP*/
class TcpSocket:public Socket{
    public:
        TcpSocket();
        int send(string message,int fd);
        int send(string message);
        string recive();
        string recive(int fd);
    public:
        int client_fd;
};

class TcpServerSocket:public TcpSocket{
    public:
        void listen();
        void accept();
};

class TcpClientSocket:public TcpSocket{
    public:
        void connect(char* ip,int port);
};
#endif