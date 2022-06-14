#pragma once
#include "Game.h"
#include "GameManager.h"
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class GameRequestHandler :
	public IRequestHandler
{
public:
	GameRequestHandler(GameManager* gameManager, LoggedUser loggedUser, RequestHandlerFactory* requestHandlerFactory,
	                   Game* game);
	~GameRequestHandler() override;
	bool isRequestRelevant(RequestInfo requestInfo) override;
	RequestResult handleRequest(RequestInfo requestInfo) override;

private:
	GameManager* m_gameManager;
	LoggedUser m_loggedUser;
	RequestHandlerFactory* m_requestHandlerFactory;
	Game* m_game;
	int questionCount;
	RequestResult getQuestion();
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults();
	RequestResult leaveGame() const;
	bool isFirstRequest;
};
