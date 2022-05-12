#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory;

class LoginRequestHandler :
	public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	LoginRequestHandler(RequestHandlerFactory* requestHandlerFactory);
	~LoginRequestHandler();
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;
private:
	RequestHandlerFactory* m_requestHandlerFactory;
	RequestResult login(RequestInfo requestInfo);
	RequestResult signup(RequestInfo requestInfo);
};
