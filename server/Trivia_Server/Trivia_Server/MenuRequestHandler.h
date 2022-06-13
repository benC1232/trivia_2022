#pragma once
#include "IRequestHandler.h"

#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;

#define LOGIN_CODE 1
#define SIGN_IN_CODE 2
#define ERROR_CODE 3
#define CREATE_ROOM_REQUEST 3
#define GET_ROOMS_REQUEST 4
#define GET_PLAYERS_IN_ROOM_REQUEST 5
#define JOIN_ROOM_REQUEST 6
#define GET_STATISTICS_REQUEST 7
#define LOGOUT_REQUEST 8
#define HIGH_SCORE_GET 10
#define ADD_QUESTION_CODE 42

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser loggedUser, RoomManager* roomManager, StatisticsManager* statisticsManager, RequestHandlerFactory* requestHandlerFactory);
	~MenuRequestHandler() override;
	bool isRequestRelevant(RequestInfo requestInfo) override;
	RequestResult handleRequest(RequestInfo requestInfo) override;
	RequestResult signout(RequestInfo requestInfo);
	RequestResult getRooms(RequestInfo requestInfo);
	RequestResult getPlayersInRoom(RequestInfo requestInfo);
	RequestResult getPersonStats(RequestInfo requestInfo);
	RequestResult getHighScore(RequestInfo requestInfo);
	RequestResult joinRoom(RequestInfo requestInfo);
	RequestResult createRoom(RequestInfo requestInfo);
	RequestResult addQuestion(RequestInfo requestInfo);

private:
	LoggedUser m_user;
	RoomManager* m_roomManager;
	StatisticsManager* m_statisticsManager;
	RequestHandlerFactory* m_requestHandlerFactory;
};
