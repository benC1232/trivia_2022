#include "LoginRequestHandler.h"
#define LOGIN_CODE 1
#define SIGN_IN_CODE 2

LoginRequestHandler::LoginRequestHandler()
{
}LoginRequestHandler::~LoginRequestHandler()
{
}
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return request.id == LOGIN_CODE || request.id == SIGN_IN_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result;
	//log in
	if (request.id == LOGIN_CODE)
	{
		LoginResponse num;
		num.status = 1;
		result.Buffer = JsonResponsePacketSerializer::serializeLoginResponse(num);
		result.newHandler = nullptr;
	}
	//sign up
	else if (request.id == SIGN_IN_CODE)
	{
		SignupResponse num;
		num.status = 2;
		result.Buffer = JsonResponsePacketSerializer::serializeSignupResponse(num);
		result.newHandler = nullptr;
	}
	else
	{
		ErrorResponse num;
		num.message = 3;
		result.Buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}