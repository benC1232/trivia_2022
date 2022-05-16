#include "LoginRequestHandler.h"

#define LOGIN_CODE 1
#define SIGN_IN_CODE 2
#define ERROR_CODE 3

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* requestHandlerFactory) : m_requestHandlerFactory(requestHandlerFactory) {}
LoginRequestHandler::~LoginRequestHandler()
{}

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
		result = login(request);
	}
	//sign up
	else if (request.id == SIGN_IN_CODE)
	{
		result = signup(request);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [login request handler has recived a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
	RequestResult result;
	LoginResponse num;
	num.status = LOGIN_CODE;
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	if (this->m_requestHandlerFactory->getLoginManager()->login(loginRequest.username, loginRequest.password)) {
		result.newHandler = new MenuRequestHandler();
		result.buffer = JsonResponsePacketSerializer::serializeLoginResponse(num);
	}
	else {
		result.newHandler = nullptr;
		num.status = ERROR_CODE;
		ErrorResponse err;
		err.message = "Login failed";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo requestInfo)
{
	RequestResult result;
	SignupResponse num;
	num.status = SIGN_IN_CODE;
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
	if (this->m_requestHandlerFactory->getLoginManager()->signup(signupRequest.username, signupRequest.password, signupRequest.email)) {
		result.newHandler = new MenuRequestHandler();
		result.buffer = JsonResponsePacketSerializer::serializeSignupResponse(num);
	}
	else {
		result.newHandler = nullptr;
		num.status = ERROR_CODE;
		ErrorResponse err;
		err.message = "Signup failed";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;
}