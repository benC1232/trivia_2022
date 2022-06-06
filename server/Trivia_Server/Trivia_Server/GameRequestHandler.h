#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "GameManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class GameRequestHandler :
	public IRequestHandler
{
public:
	GameRequestHandler(GameManager* gameManager, LoggedUser loggedUser, RequestHandlerFactory* requestHandlerFactory, Game* game);
	~GameRequestHandler();
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	GameManager* m_gameManager;
	LoggedUser m_loggedUser;
	RequestHandlerFactory* m_requestHandlerFactory;
	Game* m_game;
	int questionCount;
	RequestResult getQuestion(RequestInfo requestInfo);
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults(RequestInfo requestInfo);
	RequestResult leaveGame(RequestInfo requestInfo);
};
