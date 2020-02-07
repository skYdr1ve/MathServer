// MathServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Server.h"

int main() {
	
	/*Parser parser;
	std::string tokens = "3+4*2/(1-5)^2^3";
	auto i = parser.Parse(begin(tokens), end(tokens));
	std::cout << i->Evaluate();*/
	std::unique_ptr<Server> server(new Server);
	server->StartServer();
	server->RunServer();
}