
#ifndef _TCP_TOOLS_H
#define _TCP_TOOLS_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

int waiting_for_connect(int &server_socket, int nServerPort, int nLengthOfQueueOfListen, const char *strBoundIP);

int Connect(int &int_sorket, int nServerPort, const char *strServerIP);

#endif /* memory.h  */