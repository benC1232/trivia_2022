#include "GameRequestHandler.h"
#define LEAVE_GAME_CODE 14
#define GET_QUESTION_CODE 15
#define SUBMIT_ANSWER_CODE 16
#define GET_GAME_RESULT_CODE 17
GameRequestHandler::GameRequestHandler(GameManager* gameManager, LoggedUser loggedUser, RequestHandlerFactory* requestHandlerFactory, Game* game)
{
	this->m_gameManager = gameManager;
	this->m_loggedUser = loggedUser;
	this->m_requestHandlerFactory = requestHandlerFactory;
	this->m_game = game;
}

GameRequestHandler::~GameRequestHandler()
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == LEAVE_GAME_CODE || requestInfo.id == GET_QUESTION_CODE || requestInfo..id == SUBMIT_ANSWER_CODE || requestInfo.id == GET_GAME_RESULT_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == LEAVE_GAME_CODE)
	{
		result = leaveGame(requestInfo);
	}
	else if (requestInfo.id == GET_QUESTION_CODE)
	{
		result = getQuestion(requestInfo);
	}
	else if (requestInfo.id == SUBMIT_ANSWER_CODE)
	{
		result = submitAnswer(requestInfo);
	}
	else if (requestInfo.id == GET_GAME_RESULT_CODE)
	{
		result = getGameResults(requestInfo);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [room admin request handler has recived a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
	return RequestResult();
}