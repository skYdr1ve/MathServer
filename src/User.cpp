#include "User.h"

User::User(SOCKET _ClientSocket) {
	ClientSocket = _ClientSocket;
}

void User::Listen() {
	char recvbuf[1024];
	int iResult;
	int recvbuflen = 1024;

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			std::string input = "";
			for (int i = 0; i < iResult; i++) {
				input += recvbuf[i];
			}
			std::shared_ptr<Node> val = parser.Parse(begin(input), end(input));
			std::cout << val->Evaluate() << std::endl;
			Send(val->Evaluate());
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}

	} while (iResult > 0);
}

void User::Send(int iResult) {
	int iSendResult;
	std::string s = std::to_string(iResult);
	const char * out = s.c_str();
	std::cout << "Send: " << out << std::endl;
	iSendResult = send(ClientSocket, out, strlen(out), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}
	printf("Bytes sent: %d\n", strlen(out));
}