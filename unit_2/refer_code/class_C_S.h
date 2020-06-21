#ifndef _CLASS_C_S_H
#define _CLASS_C_S_H

#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include "tcp_tools.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
int PORT_FOR_SERVERB = 4000;
int PORT_FOR_CLIENT = 4001;

class CTCPClient
{
public:
    CTCPClient(int nServerPort, const char *strServerIP)
    {
        m_nServerPort = nServerPort;
        int nlength = strlen(strServerIP);
        m_strServerIP = new char[nlength + 1];
        strcpy(m_strServerIP, strServerIP);
    }

    virtual ~CTCPClient()
    {
        delete[] m_strServerIP;
    }

    int Run()
    {
        int sorket_int = 0;
        ClientFunction(sorket_int); //need to return nClientSocket for ::close
        // ::close(nClientSocket); //close connection

        return 0;
    }

    virtual void ClientFunction(int sorket_int)
    {
    }

protected:
    int m_nServerPort;
    char *m_strServerIP;
};

class CTCPServer
{
public:
    CTCPServer(int nServerPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL)
    {
        m_nServerPort = nServerPort;
        m_nLengthOfQueueOfListen = nLengthOfQueueOfListen;

        if (NULL == strBoundIP)
        {
            m_strBoundIP = NULL;
        }
        else
        {
            int length = strlen(strBoundIP);
            m_strBoundIP = new char[length + 1];
            memcpy(m_strBoundIP, strBoundIP, length + 1);
        }
    }

    virtual ~CTCPServer()
    {
        if (m_strBoundIP != NULL)
        {
            delete[] m_strBoundIP;
        }
    }

public:
    void *Run()
    {
        int nListenSocket = -1;
        int ret = 0;
        do
        {
            sleep(1);
            ret = waiting_for_connect(nListenSocket, m_nServerPort, 100, NULL);
        } //GET nListenSocket)
        while (ret == -1);
        sockaddr_in ClientAddress;
        socklen_t LengthOfClientAddress = sizeof(sockaddr_in);
        printf("----ready for connection----\n");
        int nConnectedSocket = ::accept(nListenSocket, (sockaddr *)&ClientAddress, &LengthOfClientAddress);
        if (-1 == nConnectedSocket)
        {
            std::cout << "accept error" << std::endl;
            ::close(nListenSocket);
            return 0;
        }

        ServerFunction(nConnectedSocket, nListenSocket);

        ::close(nConnectedSocket);
        ::close(nListenSocket);

        return 0;
    }

private:
    virtual void ServerFunction(int nConnectedSocket, int nListenSocket)
    {
    }

protected:
    int m_nServerPort;
    char *m_strBoundIP;
    int m_nLengthOfQueueOfListen;
};

class Status
{

public:
    Status(int j, char k)
    {
        i = j;
        c = k;
    }
    void print()
    {
        std::cout << "i = " << this->i << std::endl;
        std::cout << "j = " << this->c << std::endl;
    }
    void add_one()
    {
        i += 1;
    }
    void set_c(char ch)
    {
        c = ch;
    }

private:
    int i;
    char c;
};

class SerializerForStatus
{

public:
    static int Serialize(const char *pFilePath, std::vector<Status *> &v)
    {
        FILE *fp = fopen(pFilePath, "w+");
        for (int i = 0; i < v.size(); i++)
        {
            fwrite(v[i], sizeof(int) + sizeof(char), 1, fp);
        }
        fclose(fp);
        return 1;
    }

    static int Deserialize(const char *pFilePath, std::vector<Status *> &v)
    {
        FILE *fp = fopen(pFilePath, "r");
        for (int i = 0; i < v.size(); i++)
        {
            fread(v[i], sizeof(int) + sizeof(char), 1, fp);
        }
        fclose(fp);
        return 1;
    }
};

#endif /*class_c_s.h*/