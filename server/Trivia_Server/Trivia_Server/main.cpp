#include <iostream>
#include "WSAInitializer.h"
#include "Server.h"
#include <string>
int main()
{
	//took this from week 13
	WSAInitializer wsa;
	Server* server = new Server();
	try
	{
		server->run();
		std::string input = "";
		while (input != "EXIT")
		{
			std::cin >> input;
		}
		delete server;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "an exception has been thrown" << std::endl;
		delete server;
		exit(1);
	}
	return 0;
}