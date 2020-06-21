#include"sockets.h"

TcpSocket::TcpSocket(){
    _protocal="TCP";
    creat();
}

int TcpSocket::send(string message,int fd){
    char *message_c_str= (char*)message.c_str();
    int len=message.length();
    int ret=::write(fd,message_c_str,len);
    // memcpy(_source_addr,&sai,sizeof(struct sockaddr_in));
    if(ret < 0) cerr<<"failed to send, return = "<<ret<<", errno = "<<errno<<endl;
    return ret;
}

int TcpSocket::send(string message){
    // default send to _socket
    char *message_c_str= (char*)message.c_str();
    int len=message.length();
    int ret=::write(_socket,message_c_str,len);
    // memcpy(_source_addr,&sai,sizeof(struct sockaddr_in));
    if(ret < 0) cerr<<"failed to send, return = "<<ret<<", errno = "<<errno<<endl;
    return ret;
}

string TcpSocket::recive(){
    char message_c_str[BUFFSIZE];
    memset(message_c_str, 0, BUFFSIZE);
    int ret=::read(_socket,message_c_str,BUFFSIZE);
    if(ret<0){
        cerr<<"recive data failed, errorno "<<errno <<endl;
        cout<<message_c_str<<endl;
        return "";
    }else{
        // cout<<"recive from source address: "<<inet_ntoa(temp.sin_addr)<<endl;
        string message;
        message=message_c_str;
        return message;
    }
}

string TcpSocket::recive(int fd){
    char message_c_str[BUFFSIZE];
    memset(message_c_str, 0, BUFFSIZE);
    int ret=::read(fd,message_c_str,BUFFSIZE);
    if(ret<0){
        cerr<<"recive data failed, errorno "<<errno <<endl;
        cout<<message_c_str<<endl;
        return "";
    }else{
        // cout<<"recive from source address: "<<inet_ntoa(temp.sin_addr)<<endl;
        string message;
        message=message_c_str;
        return message;
    }
}

void TcpServerSocket ::listen(){
    int ret=::listen(_socket,5);
    if(ret<0){
        cerr<<"listen failed"<<endl;
    }else
    {
        cout<<"listening socket:"<<_socket<<endl;
    }
    
}

void TcpServerSocket ::accept(){
    struct sockaddr_in source_addr_in;
    bzero(&source_addr_in,sizeof(struct sockaddr_in));
    socklen_t len=sizeof(sockaddr);
    int ret=::accept(_socket,(sockaddr*)&source_addr_in,&len);
    if(ret<1){
        cerr<<"accept failed!"<<endl;
    }else
    {
        cout<<"accept succeed! from "<<inet_ntoa(source_addr_in.sin_addr)
        <<":"<<ntohs(source_addr_in.sin_port)<<endl;
    }
    _source_addr=(sockaddr_in*)malloc(sizeof(sockaddr_in));
    memcpy(_source_addr,&source_addr_in,sizeof(struct sockaddr_in));
    this->client_fd=ret;
}

void TcpClientSocket ::connect(char* ip,int port){
    struct sockaddr_in target_addr_in;
    bzero(&target_addr_in, sizeof(struct sockaddr));
    target_addr_in.sin_family = AF_INET;
    in_addr_t ip_net = inet_addr(ip);
    target_addr_in.sin_addr.s_addr = ip_net;
    target_addr_in.sin_port = htons(port);
    set_source_addr(&target_addr_in);
    int ret=::connect(_socket,(sockaddr*)&target_addr_in,sizeof(struct sockaddr));
    if(ret<0){
        cerr<<"connect failed, errno:"<<errno<<endl;
    }else{
        cout<<"connect succeed! connected to "<<ip<<":"<<port<<endl;
    }
}