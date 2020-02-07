#pragma once
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>

#define DEFAULT_PORT "1099"



class Client {
public:
	Client();
	void SetupClient();
	void Listen();
	void Send();
	void CloseClient();
private:
	WSADATA wsaData;
	SOCKET ConnectSocket;
	char recvbuf[1024];
	int recvbuflen = 1024;
};

