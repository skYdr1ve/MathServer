#include "Server.h"
#define DEFAULT_PORT "1099"

Server::Server() {
	SOCKET ListenSocket = INVALID_SOCKET;
}

void Server::StartServer() {
	
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		//поменять
		return;
	}
	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	// PCSTR = pointer constant str
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

 	bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	freeaddrinfo(result);
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	
}

void Server::RunServer() {
	std::cout << "server is run" << std::endl;
	while (true) {
		SOCKET ClientSocket = INVALID_SOCKET;

		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		std::cout << "new user: " << ClientSocket << std::endl;
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}
		std::cout << "new user was created" << std::endl;
		std::shared_ptr<User> new_user = 
			std::make_shared<User>(ClientSocket);
		users[ClientSocket] = new_user;
		workers.push_back(std::thread (&User::Listen, new_user));
	}
	
}

void Server::CloseServer() {
	closesocket(ListenSocket);
	WSACleanup();
	std::cout << "Server was stoped. You can close app" << std::endl;
}

unsigned short Server::getPort() const {
	return port;
}

void Server::setPort(const unsigned short& _port) {
	port = _port;
}