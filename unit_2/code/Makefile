include ./include/Makefile

libpath=./include/

link=-L./include -lsockets -Wl,-rpath=./include

all:main Udp Tcp

main:main.cpp
	g++ -o main main.cpp

Udp:UdpClient UdpServer

UdpClient:UdpClient.cpp 
	g++ -o UdpClient $^ $(link) -g

UdpServer:UdpServer.cpp 
	g++ -o UdpServer $^ $(link) -g

Tcp:TcpServer TcpClient

TcpServer:TcpServer.cpp
	g++ -o TcpServer $^ $(link) -g

TcpClient:TcpClient.cpp
	g++ -o TcpClient $^ $(link) -g
	
clean:
	rm -rf UdpClient 
	rm -rf UdpServer
	rm -rf ./include/libsockets.so
	rm -rf TcpClient
	rm -rf TcpServer