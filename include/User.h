#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <thread>
#include "Parser.h"

class User {
public:
	User(SOCKET _ClientSocket);

	void Listen();

	void Send(int iResult);

private:
	SOCKET ClientSocket;
	int recvbuflen = 1024;
	char recvbuf[1024];
	Parser parser;
};

