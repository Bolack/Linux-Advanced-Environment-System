#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <time.h>
#include "tcp_tools.h"
#include "class_C_S.h"

class ServerForServerB : public CTCPServer
{
public:
    ServerForServerB(int nServerPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL) : CTCPServer(nServerPort, nLengthOfQueueOfListen, strBoundIP)
    {
    }

    virtual ~ServerForServerB()
    {
    }

private:
    virtual void ServerFunction(int nConnectedSocket, int nListenSocket)
    {
        //send message to ClienB constantly
        std::cout << "nConnectedSocket:" << nConnectedSocket << std::endl;
        std::cout << "nListenSocket:" << nListenSocket << std::endl;
        int len;
        char bufsend[200] = "Server A is Online";
        int wait_count;
        while (true)
        {
            len = 0;
            wait_count = 0;
            while (len == 0)
            {
                wait_count += 1;
                if (wait_count > 20)
                {
                    std::cout << "Client disconnected" << std::endl;
                    return; // exit
                }
                sleep(2);
                len = write(nConnectedSocket, bufsend, 200); // no Info, len==0
            }
            std::cout << bufsend << std::endl;
        }
    }
};

class ServerForClient : public CTCPServer
{

public:
    ServerForClient(int nServerPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL) : CTCPServer(nServerPort, nLengthOfQueueOfListen, strBoundIP)
    {
    }
    virtual ~ServerForClient()
    {
    }

private:
    virtual void ServerFunction(int nConnectedSocket, int nListenSocket)
    {

        while (true)
        {
            std::cout << "nConnectedSocket:" << nConnectedSocket << std::endl;
            std::cout << "nListenSocket:" << nListenSocket << std::endl;
            int len;
            char bufsend[200];
            char bufrecv[200];
            int wait_count;
            Status statusOfServerA(0,'a');
            std::vector<Status *>v;
            v.push_back(&statusOfServerA);
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
                statusOfServerA.add_one();
                statusOfServerA.set_c(bufrecv[0]);
                statusOfServerA.print();
                SerializerForStatus::Serialize("ServerA.info",v);
                // std::cout<<re<<std::endl
            }
        }
    }
};

void *runForServerB(void *p)
{
    ServerForServerB serverForServerB(PORT_FOR_SERVERB);
    serverForServerB.Run();
    return 0;
}

void *runForClient(void *p)
{
    ServerForClient serverForClient(PORT_FOR_CLIENT);
    serverForClient.Run();
    return 0;
}

int main()
{
    pthread_t forServerB_id, forClient_id;
    int ret = 0;
    ret = pthread_create(&forServerB_id, NULL, runForServerB, NULL);
    // address of run
    if (ret)
    {
        std::cout << "create thread failed " << std::endl;
        return 0;
    }
    ret = pthread_create(&forClient_id, NULL, runForClient, NULL);
    if (ret)
    {
        std::cout << "create thread failed " << std::endl;
        return 0;
    }
    pthread_join(forServerB_id, NULL);
    pthread_join(forClient_id, NULL);
    return 0;
}
