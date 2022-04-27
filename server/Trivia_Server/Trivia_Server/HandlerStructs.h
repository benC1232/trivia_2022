#pragma once
#include "time.h"
#include <vector>
#include "IRequestHandler.h"
struct RequestResult
{
	std::vector<unsigned char> Buffer;
	IRequestHandler* newHandler;
};
struct RequestInfo
{
	unsigned char id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};