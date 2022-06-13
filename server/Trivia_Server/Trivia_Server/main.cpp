#include <iostream>
#include <string>
#include "Server.h"
#include "WSAInitializer.h"
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
		std::cout << "an exception has been thrown: " << e.what() << std::endl;
		delete server;
		exit(1);
	}
	return 0;
}