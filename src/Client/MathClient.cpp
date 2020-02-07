// MathClient.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Client.h"

int main()
{
	Client cl = Client();
	cl.SetupClient();
	cl.Send();
}
