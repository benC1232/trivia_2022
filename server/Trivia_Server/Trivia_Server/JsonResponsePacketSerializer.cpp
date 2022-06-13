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
#define ADD_QUESTION_RESPONSE 42


using Buffer = std::vector<unsigned char>;
/*
 * as function that converts an int into a vector of 4 bytes
 * input: num (int)
 * output: vector of 4 bytes(std::vector<unsigned char>)
 */
Buffer intToByteVector(int num) {
	Buffer buffer(4);
	for (int i = 0; i < 4; i++) buffer[3 - i] = (num << i * 8);
	return buffer;
}

/*
 * a function that cconverts a vector of room data to a string
 * input: roomData (std::vector<RoomData>)
 * output: string (std::string)
 */
std::string RoomDataVecToString(std::vector<RoomData> roomData) {
	std::string output = "";
	for (auto room : roomData) {
		output += room.name + ":" + std::to_string(room.id) + ",";
	}
	return output;
}

/*
 * a function that converts a vector of strings to a one string with , as separator
 * input: strings (std::vector<std::string>)
 * output: string (std::string)
 */
std::string stringVecToString(std::vector<std::string> strings) {
	std::string output = "";
	for (auto string : strings) {
		output += string + ",";
	}
	return output;
}

/*
 * a function that converts a vector of unsigned int to a one string with , as separator
 * input: ints (std::vector<unsigned int>)
 * output: string (std::string)
 */
std::string intVecToString(std::vector<unsigned int> ints) {
	std::string output = "";
	for (auto int_ : ints) {
		output += std::to_string(int_) + ",";
	}
	return output;
}

/*
 * a function that converts a vector of PlayerResult into a string]
 * input: pResults (std::vector<PlayerResults>)
 * output: string (std::string)
 */

std::string playerResultsVecToString(std::vector<PlayerResults> pResults) {
	std::string output = "";
	for (auto result : pResults) {
		output += result.username + "|correct answers: " + std::to_string(result.correctAnswerCount) + "|wrong answers" + std::to_string(result.wrongAnswerCount) + "|average answer time" + std::to_string(result.averageAnswerTime) + ",";
	}
	return output;
}

/*
 *a function that serialize a login response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
 * input: loginResponse (LoginResponse)
 * output: vector of unsigned char (std::vector<unsigned char>)
 */
Buffer JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse loginResponse)
{
	Buffer buffer;
	buffer.push_back(LOGIN_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"status", "" + loginResponse.status} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a signup response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: signupResponse (SignupResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse signupResponse)
{
	Buffer buffer;
	buffer.push_back(SIGNUP_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"status", "" + signupResponse.status} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize an error response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: errorResponse (ErrorResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse errorResponse)
{
	Buffer buffer;
	buffer.push_back(ERROR_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"message","" + errorResponse.message} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a logout response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: logoutResponse (LogoutResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse logoutResponse)
{
	Buffer buffer;
	buffer.push_back(LOGOUT_RESPONSE_CODE);
	nlohmann::json jsonResponse = { {"status", "" + logoutResponse.status} };
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get room response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, and the rooms vector.
  * input: getRoomResponse (GetRoomResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetRoomResponse(GetRoomResponse getRoomResponse)
{
	Buffer buffer;
	buffer.push_back(GET_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse;
	if (getRoomResponse.rooms.empty())
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
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get players in rooms response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the rooms vector.
  * input: getPlayersInRoomsResponse (GetPlayersInRoomsResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetPlayersInRoomsResponse(GetPlayersInRoomsResponse getPlayersInRoomsResponse)
{
	Buffer buffer;
	buffer.push_back(GET_PLAYERS_IN_ROOMS_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"rooms",stringVecToString(getPlayersInRoomsResponse.players)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a join room response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status.
  *	input: joinRoomResponse (JoinRoomResponse)
  *	output: vector of unsigned char (std::vector<unsigned char>)
 */
Buffer JsonResponsePacketSerializer::serializeJoinRoomResponse(JoinRoomResponse joinRoomResponse)
{
	Buffer buffer;
	buffer.push_back(JOIN_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",joinRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

/*
 * a function that serialize a create room response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
 * input: createRoomResponse (CreateRoomResponse)
 * output: vector of unsigned char (std::vector<unsigned char>)
 */
Buffer JsonResponsePacketSerializer::serializeCreateRoomResponse(CreateRoomResponse createRoomResponse)
{
	Buffer buffer;
	buffer.push_back(CREATE_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",createRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get personal stats response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, and the stats vector.
  * input: getPersonalStatsResponse (GetPersonalStatsResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetStatisticsResponse(struct GetPersonalStatsResponse getPersonalStatsResponse)
{
	Buffer buffer;
	buffer.push_back(GET_STATISTICS_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",getPersonalStatsResponse.status},
		{"stats",stringVecToString(getPersonalStatsResponse.statistics)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get high score response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, and the highscores vector.
  * input: getHighScoreResponse (GetHighScoreResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetHighScoreResponse(GetHighScoreRespnse getHighScoreResponse) {
	Buffer buffer;
	buffer.push_back(GET_STATISTICS_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",getHighScoreResponse.status},
		{"highscores",stringVecToString(getHighScoreResponse.statistics)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a close room response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: closeRoomResponse (CloseRoomResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeCloseRoomResponse(CloseRoomResponse closeRoomResponse)
{
	Buffer buffer;
	buffer.push_back(CLOSE_ROOM_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",closeRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a start game response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: startGameResponse (StartGameResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeStartGameResponse(StartGameResponse startGameResponse)
{
	Buffer buffer;
	buffer.push_back(START_GAME_RESPONSE_CODE);
	nlohmann::json jsonResponse = {
		{"status",startGameResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get room state response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, hasGameBegun, players, questionCount, and answerTimeOut.
  * input: getRoomStateResponse (GetRoomStateResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetRoomStateResponse(GetRoomStateResponse getRoomStateResponse)
{
	Buffer buffer;
	buffer.push_back(GET_ROOM_STATE_CODE);
	nlohmann::json jsonResponse = {
		{"status",getRoomStateResponse.status},
		{"hasGameBegun", getRoomStateResponse.hasGameBegun},
		{"players", stringVecToString(getRoomStateResponse.players)},
		{"questionCount", getRoomStateResponse.questionCount},
		{"answerTimeOut", getRoomStateResponse.answerTimeOut}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a leave room response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: leaveRoomResponse (LeaveRoomResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeLeaveRoomResponse(LeaveRoomResponse leaveRoomResponse)
{
	Buffer buffer;
	buffer.push_back(LEAVE_ROOM_CODE);
	nlohmann::json jsonResponse = {
		{"status",leaveRoomResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get game result response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, and the results vector.
  * input: getGameResultResponse (GetGameResultsResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetGameResultResponse(GetGameResultsResponse getGameResultResponse)
{
	Buffer buffer;
	buffer.push_back(GET_GAME_RESULT_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",getGameResultResponse.status},
		{"results", playerResultsVecToString(getGameResultResponse.results)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a submit answer response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, and the isCorrect boolean.
  * input: submitAnswerResponse (SubmitAnswerResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeSubmitAnswerResponse(SubmitAnswerResponse submitAnswerResponse)
{
	Buffer buffer;
	buffer.push_back(SUBMIT_ANSWER_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",submitAnswerResponse.status},
		{"isCorrect", submitAnswerResponse.isCorrect}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a get question response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * the json string contains the status, question, and answers vector.
  * input: getQuestionResponse (GetQuestionResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeGetQuestionResponse(GetQuestionResponse getQuestionResponse)
{
	Buffer buffer;
	buffer.push_back(GET_QUESTION_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",getQuestionResponse.status},
		{"question", getQuestionResponse.question},
		{"answers", stringVecToString(getQuestionResponse.answers)}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}

 /*
  * a function that serialize a leave game response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
  * input: leaveGameResponse (LeaveGameResponse)
  * output: vector of unsigned char (std::vector<unsigned char>)
  */
Buffer JsonResponsePacketSerializer::serializeLeaveGameResponse(LeaveGameResponse leaveGameResponse)
{
	Buffer buffer;
	buffer.push_back(LEAVE_GAME_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",leaveGameResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}


/*
 * a function that serialize add question response by converting it to a vector of unsigned char, the first byte is the message code, the next 4 bytes are the length of the json string, and the rest is the json string.
 * input: addQuestionResponse (AddQuestionResponse)
 * output: vector of unsigned char (std::vector<unsigned char>)
 */
Buffer JsonResponsePacketSerializer::serializeAddQuestionResponse(AddQuestionResponse addQuestionResponse)
{
	Buffer buffer;
	buffer.push_back(ADD_QUESTION_RESPONSE);
	nlohmann::json jsonResponse = {
		{"status",addQuestionResponse.status}
	};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	Buffer lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for (unsigned char c : jsonString) buffer.push_back(c);
	return buffer;
}
