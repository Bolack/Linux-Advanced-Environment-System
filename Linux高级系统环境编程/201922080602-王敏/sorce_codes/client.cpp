#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include"tcp_tools.h"
#include <iostream>
#include"class_C_S.h"
int SERVER_B_PORT=4000;
int CLIENT_PORT=4001;

  

class CMyTCPClient : public CTCPClient
{
public:
    CMyTCPClient(int nServerPort, const char *strServerIP) : CTCPClient(nServerPort, strServerIP)
    {
    }

    virtual ~CMyTCPClient()
    {
    }

private:
    virtual void ClientFunction(int sorket_int)
    {
		std::cout<<"connect begin"<<std::endl;
		Connect(sorket_int,m_nServerPort,m_strServerIP);
     	// std::cout<< sorket_int<<std::endl;//First Connected 
		char bufsend[200]="";
		char bufrecv[200]="";
		int sever_state;
		int wait_count; // if wait too much times the server is disconnected
		int reconnect_seconds;//seconds to reconnect
		while(true){
				::memset(bufsend,0,sizeof(bufsend));
				::memset(bufrecv,0,sizeof(bufrecv));
			    // ::strcpy(bufsend,"");
				std::cin>>bufsend; //input 
				// std::cout<<"sending sorket_int---"<<sorket_int<<std::endl;
	            sever_state= write(sorket_int,bufsend,200);
				// std:: cout<<"sever_state--"<<sever_state<<std::endl;
				socklen_t len;
				len=0;
				wait_count=0;
	         	while(len==0){
				 	// std::cout<<"waiting for server response"<<std::endl;
					len=read(sorket_int,bufrecv,200); // return: 0 no response
					// std::cout<<bufrecv<<std::endl;
					wait_count+=1;
					if(wait_count>20){
						std::cout<<"Waiting for reconnecting"<<std::endl;
						while(true){
							sleep(2);//print waiting info 1 per 2 second
							reconnect_seconds+=2;
							std::cout<<"reconnecting ,"<<reconnect_seconds<<"used"<< std::endl;
							// TODO 
							if(Connect(sorket_int,m_nServerPort+1,m_strServerIP)==1){
								std::cout<<"reconnected successfully"<<std::endl;
								std::cout<<"use seconds="<<reconnect_seconds<<std::endl;
								break;//try to reconnected untill success
							};
						}
						std::cout<<"Please write your message again"<<std::endl;
						break;//reconnected successfully, break the while
					}
				 }
				 if(bufrecv[0]=='\0')continue;//message without info after disconnected
				std::cout << "Server Response:"<<bufrecv<< std::endl;
		}
    }
};

int main()
{
	std::cout<<"begin client"<<std::endl;
    CMyTCPClient client(PORT_FOR_CLIENT, "127.0.0.1");//address and IP
    client.Run();
    return 0;
}

