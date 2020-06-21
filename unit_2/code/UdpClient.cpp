#include "./include/sockets.h"
#include<string>

#define SERVERHOST "127.0.0.1"
#define SERVERPORT 8888

int main(){
    UdpClientSocket client;
    client.set_target_addr(SERVERHOST,SERVERPORT);
    while (1)
    {
        string message;
        cin>>message;
        cout<<"client send: "<<message<<endl;
        client.send(message);
        message=client.recive();
        cout<<"server reply: "<<message<<endl;
    }
    client.close();

}