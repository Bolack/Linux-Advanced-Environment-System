#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include "tcp_tools.h"




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
	int Run()
	{
		int nListenSocket = -1;
		waiting_for_connect(nListenSocket,m_nServerPort,100,NULL);//GET nListenSocket
		sockaddr_in ClientAddress;
		socklen_t LengthOfClientAddress = sizeof(sockaddr_in);
		printf("----ready for connection----\n");
		int nConnectedSocket = ::accept(nListenSocket, (sockaddr *)&ClientAddress, &LengthOfClientAddress);
		if (-1 == nConnectedSocket)
		{
			std::cout << "accept error" << std::endl;
			::close(nListenSocket);
			return -1;
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

private:
	int m_nServerPort;
	char *m_strBoundIP;
	int m_nLengthOfQueueOfListen;
};

class CMyTCPServer : public CTCPServer
{
public:
	CMyTCPServer(int nServerPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL) : CTCPServer(nServerPort, nLengthOfQueueOfListen, strBoundIP)
	{
	}

	virtual ~CMyTCPServer()
	{
	}

private:
	virtual void ServerFunction(int nConnectedSocket, int nListenSocket)
	{
		std::cout << "nConnectedSocket:" << nConnectedSocket << std::endl;
		std::cout << "nListenSocket:" << nListenSocket << std::endl;
		int len;
		char bufsend[200];
		char bufrecv[200];
		int wait_count;
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
			// std::cout<<re<<std::endl
		}
	}
};
// TODO if disconnected
int main()
{
	CMyTCPServer myserver(4000);
	myserver.Run();
	return 0;
}
