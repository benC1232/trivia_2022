#pragma once
#include "json.hpp"
#include <string>
#include <vector>
#include<bitset>
#include <iomanip>
#include <sstream>
#include "Room.h"
#define START_OF_JSON_SECTION 5

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

class JsonResponsePacketSerializer {
public:
	static std::vector<unsigned char> serializeLoginResponse(struct LoginResponse loginResponse);
	static std::vector<unsigned char> serializeSignupResponse(struct SignupResponse signupResponse);
	static std::vector<unsigned char> serializeErrorResponse(struct ErrorResponse errorResponse);
	static std::vector<unsigned char> serializeLogoutResponse(struct LogoutResponse logoutResponse);
	static std::vector<unsigned char> serializeGetRoomResponse(struct GetRoomResponse getRoomResponse);
	static std::vector<unsigned char> serializeGetPlayersInRoomsResponse(struct GetPlayersInRoomsResponse getPlayersInRoomsResponse);
	static std::vector<unsigned char>  serializeJoinRoomResponse(struct JoinRoomResponse joinRoomResponse);
	static std::vector<unsigned char>  serializeCreateRoomResponse(struct CreateRoomResponse createRoomResponse);
	static std::vector<unsigned char> serializeGetStatisticsResponse(struct GetPersonalStatsResponse getPresonalStatsResponse);
	static std::vector<unsigned char> serializeGetHighScoreResponse(struct GetHighScoreRespnse getHighScoreResponse);
};