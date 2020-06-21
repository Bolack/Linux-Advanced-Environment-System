#include"sockets.h"

int Socket::creat()
{

    /* code */
    if (_protocal == "TCP")
        _socket = socket(AF_INET, SOCK_STREAM, 0);
    else if (_protocal == "UDP")
        _socket = socket(AF_INET, SOCK_DGRAM, 0);
    else if (_protocal == "UNIXDOMIN")
        _socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (_socket < 0)
    {
        cerr << "creat socket error" << endl;
    }else{
        cout << "socket is created successfully and it is "<<_socket<<endl; 
    }
    return _socket;
}

int Socket::_set_bind_sockaddr(char* ip, int port)
{
    struct sockaddr_in target_addr_in;
    bzero(&target_addr_in, sizeof(struct sockaddr));
    if (_protocal == "TCP" | _protocal == "UDP")
    {
        target_addr_in.sin_family = AF_INET;
    }
    else if (_protocal == "UNIXDOMIN")
    {
        target_addr_in.sin_family = AF_UNIX;
    }
    in_addr_t ip_net = inet_addr(ip);
    target_addr_in.sin_addr.s_addr = ip_net;
    target_addr_in.sin_port = htons(port);
    _bind_sockaddr = * (sockaddr *)&target_addr_in;
    return 1;
}

bool Socket::bind(char* ip="127.0.0.1", int port=8001){
    _set_bind_sockaddr(ip,port);
    int len=sizeof(_bind_sockaddr);
    int ret=::bind(_socket,&_bind_sockaddr,len);
    if(ret<0)
    {
        cerr<<"bind failed"<<endl;
        return false;
    }else
    {
        cout<<"bind successfully"<<" socket:"<<ip<<":"<<port<<endl;
        return true;
    }
}

int Socket::send(string message){
    cout<<"base send"<<endl;
}

void Socket::set_source_addr(sockaddr_in *source_addr){
    _source_addr=(sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    memcpy(_source_addr,source_addr,sizeof(struct sockaddr_in));

    // struct sockaddr_in *sa;
    // sa=_source_addr;W
    // cout<<"udpsockets.h 63,source address: "<<inet_ntoa(sa->sin_addr)<<endl;
}

void Socket::get_source_addr(struct sockaddr_in *source_addr){
    // source_addr=this->_source_addr; 
    memcpy(source_addr,_source_addr,sizeof(struct sockaddr_in));
}
