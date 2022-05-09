#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"
class LoginRequestHandler :
	public IRequestHandler
{
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_requestHandlerFactory;
	
public:
	LoginRequestHandler(LoginManager& lm, RequestHandlerFactory& rhf);
	~LoginRequestHandler();
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;
	RequestResult login(RequestInfo ri);
	RequestResult signup(RequestInfo ri);
};
