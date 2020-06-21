#include "sockets.h"

UdpSocket::UdpSocket(){
        _protocal="UDP";
        creat();
}

void UdpSocket::set_target_addr(char* ip="127.0.0.1", int port=8888){
    struct sockaddr_in target_addr_in;
    bzero(&target_addr_in,sizeof(struct sockaddr_in));
    target_addr_in.sin_family=AF_INET;
    in_addr_t ip_net=inet_addr(ip);
    target_addr_in.sin_addr.s_addr=ip_net;
    target_addr_in.sin_port=htons(port);
    // _target_addr=&target_addr_in;
    _target_addr=(sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    memcpy(_target_addr,&target_addr_in,sizeof(struct sockaddr_in));
}

void UdpSocket::set_target_addr(sockaddr_in *target_addr){
    _target_addr=(sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    memcpy(_target_addr,target_addr,sizeof(struct sockaddr_in));
    // cout<<"recive from source address: "<<inet_ntoa(_target_addr->sin_addr)<<endl;
}

int UdpSocket::send(string message){
    char *message_c_str= (char*)message.c_str();
    int len=message.length();
    socklen_t sockaddr_len =sizeof(struct sockaddr);
    // char buf[BUFFSIZE]="hello test\n";
    // sockaddr_in sai;
    // memset(&sai,0,sizeof(struct sockaddr_in));
    // memset(_source_addr,0,sizeof(struct sockaddr_in));
    int ret=sendto(_socket,message_c_str,BUFFSIZE,0,
                    (sockaddr*)_target_addr,sockaddr_len);
    // memcpy(_source_addr,&sai,sizeof(struct sockaddr_in));
    if(ret < 0) cerr<<"failed to send, return = "<<ret<<", errno = "<<errno<<endl;
    return ret;
}

string UdpSocket::recive(){
    char message_c_str[BUFFSIZE];
    memset(message_c_str, 0, BUFFSIZE);
    // bzero(_source_addr,sizeof(struct sockaddr));
    socklen_t len= sizeof(struct sockaddr); // out_in reference # FIXME
    sockaddr_in temp;
    int ret=recvfrom(_socket,message_c_str,BUFFSIZE+1,
                0,(sockaddr*)&temp,&len);
    set_source_addr(&temp);
    if(ret<0){
        cerr<<"recive data failed, errorno "<<errno <<endl;
        return "";
    }else{
        // cout<<"recive from source address: "<<inet_ntoa(temp.sin_addr)<<endl;
        string message;
        message=message_c_str;
        return message;
    }

}
