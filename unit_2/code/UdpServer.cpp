#include "./include/sockets.h"
#define HOST "0.0.0.0" // bind host
#define PORT 8888

int main(){
    UdpServerSocket server=UdpServerSocket();
    server.bind(HOST,PORT);
    while (1)
    {
        string message=server.recive();
        struct sockaddr_in *sa;
        server.get_source_addr(sa);
        cout<<"source address: "<<inet_ntoa(sa->sin_addr)<<":"<<ntohs(sa->sin_port)<<endl;
        cout<<"messsage is: "<<message<<endl;
        server.set_target_addr(sa);
        server.send(message);
    }
    server.close();
}