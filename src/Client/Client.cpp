#include "Client.h"

Client::Client() {
	ConnectSocket = INVALID_SOCKET;
}

void Client::SetupClient() {

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	const char *sendbuf = "this is a test";

	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("192.168.100.2", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	ptr = result;
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		return;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return;
	}
}

void Client::CloseClient() {
	if (shutdown(ConnectSocket, SD_SEND) == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}
	closesocket(ConnectSocket);
	WSACleanup();
	std::cout << "Client was stoped. You can close app" << std::endl;
}

void Client::Listen() {

	int iResult;

	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		std::cout << iResult << std::endl;
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			std::cout << "Result is ";
			for (int i = 0; i < iResult; i++)
				std::cout << recvbuf[i];
			std::cout << std::endl;
			std::cout << "Input math expression: ";
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);

}

void Client::Send() {
	std::thread thr(&Client::Listen, this);

	int iResult;

	std::string sendbuf;
	
	do {
		std::cout << "Input math expression: ";
		getline(std::cin, sendbuf);
		if (sendbuf == "bye") {
			this->CloseClient();
			return;
		}
		iResult = send(ConnectSocket, sendbuf.c_str(), (int)strlen(sendbuf.c_str()), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return;
		}
	} while (iResult > 0);
	printf("Bytes Sent: %ld\n", iResult);
}