#pragma once
#include "time.h"
#include <vector>
#include "IRequestHandler.h"
//הכלה מעגלית שלקחה לי 4 שעות מהחיים
class IRequestHandler;
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