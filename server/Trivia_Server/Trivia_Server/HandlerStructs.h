#pragma once
#include <vector>
#include "IRequestHandler.h"
//���� ������ ����� �� 4 ���� ������
class IRequestHandler;


struct RequestResult
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;
};

struct RequestInfo
{
	unsigned char id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};
