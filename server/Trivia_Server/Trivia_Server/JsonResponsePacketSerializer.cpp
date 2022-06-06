#include "JsonResponsePacketSerializer.h"

//the first byte of the vector is the msg type
#define LOGIN_RESPONSE_CODE 1
#define SIGNUP_RESPONSE_CODE 2
#define ERROR_RESPONSE_CODE 3
#define LOGOUT_RESPONSE_CODE 4
#define GET_ROOM_RESPONSE_CODE 5
#define GET_PLAYERS_IN_ROOMS_RESPONSE_CODE 6
#define JOIN_ROOM_RESPONSE_CODE 7
#define CREATE_ROOM_RESPONSE_CODE 8
#define GET_STATISTICS_RESPONSE_CODE 9
#define CLOSE_ROOM_RESPONSE_CODE 10
#define START_GAME_RESPONSE_CODE 11
#define GET_ROOM_STATE_CODE 12
#define LEAVE_ROOM_CODE 13
#define LEAVE_GAME_RESPONSE 14
#define GET_QUESTION_RESPONSE 15
#define SUBMIT_ANSWER_RESPONSE 16
#define GET_GAME_RESULT_RESPONSE 17

std::vector<unsigned char> intToByteVector(int num) {
	std::vector<unsigned char> buffer(4);
	for (int i = 0; i < 4; i++) buffer[3 - i] = (num << i * 8);
	return buffer;
}

std::string RoomDataVecToString(std::vector<RoomData> roomData) {
	std::string output = "";
	for (auto room : roomData) {
		output += room.name + ":" + std::to_string(room.id)+ ",";
	}
	return output;
}

std::string stringVecToString(std::vector<std::string> strings) {
	std::string output = "";
	for (auto string : strings) {
		output += string + ",";
	}
	return output;
}

std::string intVecToString(std::vector<unsigned int> ints) {
	std::string output = "";
	for (auto int_ : ints) {
		output += std::to_string(int_) + ",";
	}
	return output;
}

std::string playerResultsVecToString(std::vector<PlayerResults> pResults) {
	std::string output = "";
	for (auto result : pResults) {
		output += result.username+":" + std::to_string(result.correctAnswerCount)+":"+ std::to_string(result.wrongAnswerCount)+":"+std::to_string(result.averageAnswerTime) + ",";
	}
	return output;
}


nlohmann::json answerMapToJson(std::map<unsigned int, std::string> answers) {
	nlohmann::json output;
	for (auto answer : answers) {
		output[std::to_string(answer.first)] = answer.second;
	}
	return output;
}


std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse loginResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(LOGIN_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"status", "" + loginResponse.status} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse signupResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(SIGNUP_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"status", "" + signupResponse.status} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse errorResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(ERROR_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"message","" + errorResponse.message} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse logoutResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(LOGOUT_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"status", "" + logoutResponse.status} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomResponse(GetRoomResponse getRoomResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse;
	if (getRoomResponse.rooms.size() == 0)
	{
		jsonResponse = {
		   {"status",  getRoomResponse.status},
		   {"rooms", "no rooms available"}
		};
	}
	else
	{
		jsonResponse = {
			{"status", getRoomResponse.status},
			{"rooms",  RoomDataVecToString(getRoomResponse.rooms)}
		};
	}
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomsResponse(GetPlayersInRoomsResponse getPlayersInRoomsResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_PLAYERS_IN_ROOMS_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"rooms",stringVecToString(getPlayersInRoomsResponse.players)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(JoinRoomResponse joinRoomResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(JOIN_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",joinRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(CreateRoomResponse createRoomResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(CREATE_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",createRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetStatisticsResponse(struct GetPersonalStatsResponse getPresonalStatsResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_STATISTICS_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",getPresonalStatsResponse.status},
		{"stats",stringVecToString(getPresonalStatsResponse.statistics)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetHighScoreResponse(GetHighScoreRespnse getHighScoreResponse) {
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_STATISTICS_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",getHighScoreResponse.status},
		{"highscores",stringVecToString(getHighScoreResponse.statistics)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCloseRoomResponse(CloseRoomResponse closeRoomResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(CLOSE_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",closeRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeStartGameResponse(StartGameResponse startGameResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(START_GAME_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",startGameResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomStateResponse(GetRoomStateResponse getRoomStateResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_ROOM_STATE_CODE);
	nlohmann::json jsonResponse = {
		{"status",getRoomStateResponse.status},
		{"hasGameBegun", (getRoomStateResponse.hasGameBegun ? 1 : 0)},
		{"players", stringVecToString(getRoomStateResponse.players)},
		{"questionCount", getRoomStateResponse.questionCount},
		{"answerTimeOut", getRoomStateResponse.answerTimeOut}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveRoomResponse(LeaveRoomResponse leaveRoomResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(LEAVE_ROOM_CODE);
	nlohmann::json jsonResponse = {
		{"status",leaveRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetGameResultResponse(GetGameResultsResponse getGameResultResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_GAME_RESULT_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",getGameResultResponse.status},
		{"results", playerResultsVecToString(getGameResultResponse.results)}

	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}


std::vector<unsigned char> JsonResponsePacketSerializer::serializeSubmitAnswerResponse(SubmitAnswerResponse submitAnswerResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(SUBMIT_ANSWER_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",submitAnswerResponse.status},
		{"isCorrect", submitAnswerResponse.isCorrect}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetQuestionResponse(GetQuestionResponse getQuestionResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(GET_QUESTION_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",getQuestionResponse.status},
		{"question", getQuestionResponse.question},
		{"answers", stringVecToString(getQuestionResponse.answers)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveGameResponse(LeaveGameResponse leaveGameResponse)
{
	std::vector<unsigned char> buffer;
	buffer.push_back(LEAVE_GAME_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",leaveGameResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}


