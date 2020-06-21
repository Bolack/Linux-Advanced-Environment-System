#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include "tcp_tools.h"
#include <sys/socket.h>
#include "class_C_S.h"
#include <vector>

int SERVER_B_PORT = 4000;
int CLIENT_PORT = 4001;

class ClientB : public CTCPClient
{
public:
    ClientB(int nServerPort, const char *strServerIP) : CTCPClient(nServerPort, strServerIP)
    {
    }

    virtual ~ClientB()
    {
    }
private:
    virtual void ClientFunction(int sorket_int)
    {

        Connect(sorket_int, m_nServerPort, m_strServerIP);
        std::cout << "connecte to " << m_strServerIP << ":" << m_nServerPort << " successfully" << std::endl;
        // std::cout<< sorket_int<<std::endl;//First Connected
        // TODO constantly recive a str  from Client A
        char bufrecv[200] = "";
        int sever_state;
        int wait_count;        // if wait too much times the server is disconnected
        int reconnect_seconds; //seconds to reconnect
        while (true)
        {
            ::memset(bufrecv, 0, sizeof(bufrecv));
            socklen_t len;
            len = 0;
            wait_count = 0;
            while (len == 0)
            {
                len = read(sorket_int, bufrecv, 200); // return: 0 no response
                if (bufrecv[0] != '\0')
                    std::cout << bufrecv << std::endl;
                wait_count += 1;
                if (wait_count > 20)
                {
                    std::cout << "Server A Disconnect" << std::endl;
                    return;
                }
            }
        }
    }
};
class ServerB : public CTCPServer
{
public:
    ServerB(int nServerPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL) : CTCPServer(nServerPort, nLengthOfQueueOfListen, strBoundIP)
    {
    }
    virtual ~ServerB()
    {
    }
    virtual void ServerFunction(int nConnectedSocket, int nListenSocket)
    {
        /* READING THE STATUS OF SERVERA*/
        Status statusOfA(0, 'a');
        std::vector<Status *> v;
        v.push_back(&statusOfA);
        SerializerForStatus ::Deserialize("ServerA.info", v);
        //send message to ClienB constantly

        while (true)
        {
            std::cout << "nConnectedSocket:" << nConnectedSocket << std::endl;
            std::cout << "nListenSocket:" << nListenSocket << std::endl;
            int len;
            char bufsend[200];
            char bufrecv[200];
            int wait_count;
            std::vector<Status *> v_stores;
            v_stores.push_back(&statusOfA);
            while (true)
            {
                ::memset(bufrecv, 0, sizeof(bufrecv));
                ::memset(bufsend, 0, sizeof(bufsend));
                //waiting for input
                len = 0;
                wait_count = 0;
                while (len == 0)
                {
                    std::cout << "waiting for client" << std::endl;
                    std::cout << "nListenSocket" << nListenSocket << std::endl;
                    wait_count += 1;
                    if (wait_count > 20)
                    {
                        std::cout << "Client disconnected" << std::endl;
                        return; // exit
                    }
                    // Why I can't recieve info
                    len = read(nConnectedSocket, bufrecv, 200); // no Info, len==0
                    std::cout << "bufrecv:" << std::endl;
                    std::cout << bufrecv << std::endl;
                }
                std::cout << bufrecv << std::endl;
                // printf("if connect");
                // ::write(nConnectedSocket, "hello",200);
                ::write(nConnectedSocket, bufrecv, 200);
                statusOfA.add_one();
                statusOfA.set_c(bufrecv[0]);
                statusOfA.print();
                SerializerForStatus::Serialize("ServerA.info", v_stores);
                // std::cout<<re<<std::endl
            }
        }
    }
};

    int main()
    {
        std::cout << "now serverB is a  client" << std::endl;
        ClientB client(PORT_FOR_SERVERB, "127.0.0.1"); //address and IP
        client.Run();
        sleep(3);
        ServerB serverB(PORT_FOR_CLIENT+1);
        serverB.Run();
        std::cout << "ServerB is offering service" << std::endl;
        return 0;
    }
