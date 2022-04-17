#pragma once
#include "Communicator.h"
#include <thread>
class Server
{
public:
	~Server();
	Server();
	void run();
private:
	Communicator* m_communicator;
};
