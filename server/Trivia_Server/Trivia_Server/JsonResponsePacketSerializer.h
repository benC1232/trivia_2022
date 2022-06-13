#pragma once
#include "json.hpp"
#include <string>
#include <vector>
#include <map>
#include<bitset>
#include <iomanip>
#include <sstream>
#include "Room.h"
#define START_OF_JSON_SECTION 5

using Buffer = std::vector<unsigned char>;

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct ErrorResponse {
	std::string message;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomsResponse {
	std::vector<std::string> players;
};

struct GetHighScoreRespnse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};

struct CloseRoomResponse {
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeOut;
};

struct LeaveRoomResponse {
	unsigned int status;
};

struct LeaveGameResponse {
	unsigned int status;
};

struct GetQuestionResponse {
	unsigned int status;
	std::string question;
	std::vector<std::string> answers;

};

struct SubmitAnswerResponse {
	unsigned int status;
	bool isCorrect;
};

typedef struct{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} PlayerResults ;

struct GetGameResultsResponse {
	unsigned int status;
	std::vector<PlayerResults> results;
};

class JsonResponsePacketSerializer {
public:
	static Buffer serializeLoginResponse(struct LoginResponse loginResponse);
	static Buffer serializeSignupResponse(struct SignupResponse signupResponse);
	static Buffer serializeErrorResponse(struct ErrorResponse errorResponse);
	static Buffer serializeLogoutResponse(struct LogoutResponse logoutResponse);
	static Buffer serializeGetRoomResponse(struct GetRoomResponse getRoomResponse);
	static Buffer serializeGetPlayersInRoomsResponse(struct GetPlayersInRoomsResponse getPlayersInRoomsResponse);
	static Buffer serializeJoinRoomResponse(struct JoinRoomResponse joinRoomResponse);
	static Buffer serializeCreateRoomResponse(struct CreateRoomResponse createRoomResponse);
	static Buffer serializeGetStatisticsResponse(struct GetPersonalStatsResponse getPresonalStatsResponse);
	static Buffer serializeGetHighScoreResponse(struct GetHighScoreRespnse getHighScoreResponse);
	static Buffer serializeCloseRoomResponse(struct CloseRoomResponse closeRoomResponse);
	static Buffer serializeStartGameResponse(struct StartGameResponse startGameResponse);
	static Buffer serializeGetRoomStateResponse(struct GetRoomStateResponse getRoomStateResponse);
	static Buffer serializeLeaveRoomResponse(struct LeaveRoomResponse leaveRoomResponse);
	static Buffer serializeGetGameResultResponse(struct GetGameResultsResponse getGameResultResponse);
	static Buffer serializeSubmitAnswerResponse(struct SubmitAnswerResponse submitAnswerResponse);
	static Buffer serializeGetQuestionResponse(struct GetQuestionResponse getQuestionResponse);
	static Buffer serializeLeaveGameResponse(struct LeaveGameResponse leaveGameResponse);
};