#pragma once
#include "HandlerStructs.h"
//הכלה מעגלית שלקחה לי 4 שעות מהחיים
struct RequestResult;
struct RequestInfo;

class IRequestHandler
{
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo request) = 0;
};
