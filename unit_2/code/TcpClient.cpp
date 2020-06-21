#include"./include/sockets.h"

int main(){
    TcpClientSocket client;
    client.connect("127.0.0.1",8001);
    string message;
    while (1)
    {
        cin>>message;
        client.send(message);
        message=client.recive();
        cout<<"echo: "<<message<<endl;
    }
}