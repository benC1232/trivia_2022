#include "LoginRequestHandler.h"
#include <regex>
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

RequestResult LoginRequestHandler::login(RequestInfo requestInfo) const
{
	RequestResult result;
	LoginResponse num;
	num.status = LOGIN_CODE;
	const LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	if (this->m_requestHandlerFactory->getLoginManager()->login(loginRequest.username, loginRequest.password)) {
		result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(LoggedUser(loginRequest.username));
		result.buffer = JsonResponsePacketSerializer::serializeLoginResponse(num);
	}
	else {
		result.newHandler = this->m_requestHandlerFactory->createLoginRequestHandler();
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
	// checking if the fields are valid with regex
	std::regex usernameRegex("^[a-zA-Z0-9_]+$");
	std::regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$");
	std::regex emailRegex("^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}$");
	if (std::regex_match(signupRequest.username, usernameRegex) && std::regex_match(signupRequest.password, passwordRegex) && std::regex_match(signupRequest.email, emailRegex))
	{
		throw std::exception("invalid username or password or email");
	}
	if (this->m_requestHandlerFactory->getLoginManager()->signup(signupRequest.username, signupRequest.password, signupRequest.email)) {
		result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(LoggedUser(signupRequest.username));
		result.buffer = JsonResponsePacketSerializer::serializeSignupResponse(num);
	}
	else {
		result.newHandler = this->m_requestHandlerFactory->createLoginRequestHandler();
		num.status = ERROR_CODE;
		ErrorResponse err;
		err.message = "Signup failed";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(err);
	}
	return result;
}