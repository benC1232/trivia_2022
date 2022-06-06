#include "GameRequestHandler.h"

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
	return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	return RequestResult();
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