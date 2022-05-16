#pragma once
#include "IRequestHandler.h"
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	virtual bool isRequestRelevant(RequestInfo request) override;
	virtual RequestResult handleRequest(RequestInfo request) override;
};
