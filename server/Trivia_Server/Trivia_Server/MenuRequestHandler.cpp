#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}
