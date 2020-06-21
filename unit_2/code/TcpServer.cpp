#include"./include/sockets.h"

int main(){
    TcpServerSocket server;
    server.bind("0.0.0.0",8001);
    server.listen();
    string message;
    while (1)
    {
        if(message=="")server.accept();
        message=server.recive(server.client_fd);
        cout<<"recive message: "<<message<<endl;
        server.send(message,server.client_fd);
    }
}