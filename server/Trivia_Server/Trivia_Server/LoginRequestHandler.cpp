#include "LoginRequestHandler.h"
#include <regex>
#define LOGIN_CODE 1
#define SIGN_IN_CODE 2
#define ERROR_CODE 3

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* requestHandlerFactory) : m_requestHandlerFactory(
	requestHandlerFactory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return request.id == LOGIN_CODE || request.id == SIGN_IN_CODE;
}
/*
* function handles the requests that this part of the state machine is responsible for
* input: request - the request that is being handled
* output: the response that is being sent to the client
*/
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
		try
		{
			result = signup(request);
		}
		catch (std::exception& e)
		{
			ErrorResponse num;
			num.message = e.what();
			result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
			result.newHandler = this;
		}
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [login request handler has received a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = this;
	}
	return result;
}
/*
* function handles the login request
* input: requestInfo - the request info
* output: the request result
*/
RequestResult LoginRequestHandler::login(RequestInfo requestInfo) const
{
	RequestResult result;
	LoginResponse num;
	num.status = LOGIN_CODE;
	const LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	if (this->m_requestHandlerFactory->getLoginManager()->login(loginRequest.username, loginRequest.password))
	{
		result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(LoggedUser(loginRequest.username));
		result.buffer = JsonResponsePacketSerializer::serializeLoginResponse(num);
	}
	else
	{
		result.newHandler = this->m_requestHandlerFactory->createLoginRequestHandler();
		num.status = ERROR_CODE;
		ErrorResponse err;
		err.message = "Login failed";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;
}
/*
* function handles the sign up request
* input: requestInfo - the request info
* output: the request result
*/
RequestResult LoginRequestHandler::signup(RequestInfo requestInfo)
{
	RequestResult result;
	SignupResponse num;
	num.status = SIGN_IN_CODE;
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
	// checking if the fields are valid with regex
	std::regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*#?&])[A-Za-z\\d@$!%*#?&]{8,}$");
	std::regex emailRegex("^[a-zA-Z0-9.+_-]+@[a-zA-Z0-9._-]+\\.[a-zA-Z]+$");
	if (!(std::regex_match(signupRequest.password, passwordRegex) && std::regex_match(signupRequest.email, emailRegex)))
	{
		throw std::exception("invalid password or email, password must contain at least 8 characters, 1 uppercase, 1 lowercase, 1 number and one of the next characters !@#$%^&*");
	}
	if (this->m_requestHandlerFactory->getLoginManager()->signup(signupRequest.username, signupRequest.password,
		signupRequest.email))
	{
		result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(LoggedUser(signupRequest.username));
		result.buffer = JsonResponsePacketSerializer::serializeSignupResponse(num);
	}
	else
	{
		result.newHandler = this->m_requestHandlerFactory->createLoginRequestHandler();
		num.status = ERROR_CODE;
		ErrorResponse err;
		err.message = "Signup failed";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;
}