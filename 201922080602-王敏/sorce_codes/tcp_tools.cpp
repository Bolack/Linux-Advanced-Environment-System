#include "tcp_tools.h"

int waiting_for_connect(int &server_socket, int nServerPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL)
/***
     *  return: int  
     *  &listenSocket (server)
    ***/
{
	int m_nServerPort;
	char *m_strBoundIP;
	int m_nLengthOfQueueOfListen;

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
	{
		server_socket = ::socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == server_socket)
		{
			std::cout << "socket error" << std::endl;
			return -1;
		}

		sockaddr_in ServerAddress;
		memset(&ServerAddress, 0, sizeof(sockaddr_in));//zero_set
		ServerAddress.sin_family = AF_INET;

		if (NULL == m_strBoundIP)
		{
			ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else
		{
			if (::inet_pton(AF_INET, m_strBoundIP, &ServerAddress.sin_addr) != 1)
			{
				std::cout << "inet_pton error" << std::endl;
				::close(server_socket);
				return -1;
			}
		}

		ServerAddress.sin_port = htons(m_nServerPort);

		if (::bind(server_socket, (sockaddr *)&ServerAddress, sizeof(sockaddr_in)) == -1)
		{
			std::cout << "bind error" << std::endl; //interval is little
			::close(server_socket);
			return -1;
		}

		if (::listen(server_socket, m_nLengthOfQueueOfListen) == -1)
		{
			std::cout << "listen error" << std::endl;
			::close(server_socket);
			return -1;
		}
		return 1;
	}
}

int Connect(int &int_sorket, int nServerPort, const char *strServerIP)
/***
 * return int_sorket(client)
 * **/

{   
	// TODO several state to handle different error
	// need to use this function more than one time
	int m_nServerPort;
	char *m_strServerIP;
	m_nServerPort = nServerPort;
	int nlength = strlen(strServerIP);
	m_strServerIP = new char[nlength + 1];
	strcpy(m_strServerIP, strServerIP);

	int_sorket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == int_sorket)
	{
		std::cout << "socket error" << std::endl;
		return -1;
	}

	sockaddr_in ServerAddress;
	memset(&ServerAddress, 0, sizeof(sockaddr_in)); // zero setting
	ServerAddress.sin_family = AF_INET;
	if (::inet_pton(AF_INET, m_strServerIP, &ServerAddress.sin_addr) != 1)
	{
		std::cout << "inet_pton error" << std::endl;
		::close(int_sorket);
		return -1;
	}
	ServerAddress.sin_port = htons(m_nServerPort); // assign values to SeverAddress

	// this place will send infomation to read
	if (::connect(int_sorket, (sockaddr *)&ServerAddress, sizeof(sockaddr_in)) == -1)
	{
		std::cout << "connect error, tring to reconnect" << std::endl;
		::close(int_sorket);
		return -1;
	}
	return 1;
}