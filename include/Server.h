#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "User.h"

class Server {
public:
	Server();

	void StartServer();
	void RunServer();
	void CloseServer();
	unsigned short getPort() const;
	void setPort(const unsigned short& _port);

private:
	SOCKET ListenSocket;
	WSAData wsaData;
	unsigned short port = 1099;
	std::vector<std::thread> workers;
	std::map<SOCKET, std::shared_ptr<User>> users;
};

