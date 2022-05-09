#include "LoginRequestHandler.h"

#define LOGIN_CODE 1
#define SIGN_IN_CODE 2

LoginRequestHandler::LoginRequestHandler(LoginManager& lm, RequestHandlerFactory& rhf): m_loginManager(lm), m_requestHandlerFactory(rhf) {}
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
		result.Buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo ri)
{
	RequestResult result;
	LoginResponse num;
	num.status = 1;
	LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(ri.buffer);
	if (this->m_loginManager.login(lr.username, lr.password)) {
		result.newHandler = new MenuRequestHandler();
		result.Buffer = JsonResponsePacketSerializer::serializeLoginResponse(num);
	}
	else {
		result.newHandler = nullptr;
		num.status = 3;
		ErrorResponse err;
		err.message = "Login failed";
		result.Buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;

	
}

RequestResult LoginRequestHandler::signup(RequestInfo ri)
{
	RequestResult result;
	SignupResponse num;
	num.status = 2;
	SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(ri.buffer);
	if (this->m_loginManager.signup(sr.username, sr.password, sr.email)) {
		result.newHandler = new MenuRequestHandler();
		result.Buffer = JsonResponsePacketSerializer::serializeSignupResponse(num);
	}
	else {
		result.newHandler = nullptr;
		num.status = 3;
		ErrorResponse err;
		err.message = "Signup failed";
		result.Buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;
		
}
