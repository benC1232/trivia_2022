#include "JsonRequestPacketDeserializer.h"

/*
function parses the json part of a packet and returns the content of the fields
input: vector of unsigned chars (bytes) representing the json string
output: the content of the fields in the json
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string username = jsonObject["username"];
	std::string password = jsonObject["password"];
	LoginRequest parsedData;
	parsedData.password = password;
	parsedData.username = username;
	return parsedData;
}
/*
function parses the json part of a packet and returns the content of the fields
input: vector of unsigned chars (bytes) representing the json string
output: the content of the fields in the json
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string username = jsonObject["username"];
	std::string password = jsonObject["password"];
	std::string email = jsonObject["email"];
	SignupRequest parsedData;
	parsedData.email = email;
	parsedData.password = password;
	parsedData.username = username;
	return parsedData;
}
/*
* function parses the json part of a packet and returns the content of the fields
* input: vector of unsigned chars (bytes) representing the json string
* output: the content of the fields in the json
*/
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string roomId = jsonObject["roomId"];
	GetPlayersInRoomRequest parsedData;
	try
	{
		parsedData.roomId = atoi(roomId.c_str());
	}
	catch (...)
	{
		throw std::exception("roomId is not a number");
	}
	return parsedData;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string roomId = jsonObject["roomId"];
	JoinRoomRequest parsedData;
	try
	{
		parsedData.roomId = atoi(roomId.c_str());
	}
	catch (...)
	{
		throw std::exception("roomId is not a number");
	}
	return parsedData;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string roomName = jsonObject["roomName"];
	int maxUsers = jsonObject["maxUsers"];
	int questionCount = jsonObject["questionCount"];
	int answerTimeout = jsonObject["answerTimeout"];
	CreateRoomRequest parsedData;
	try
	{
		parsedData.answerTimeout = answerTimeout;
		parsedData.maxUsers = maxUsers;
		parsedData.questionCount = questionCount;
		parsedData.roomName = roomName;
	}
	catch (...)
	{
		throw std::exception("maxUsers, questionNumber or answerTimeout is not a number");
	}
	return parsedData;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string answer = jsonObject["answer"];
	SubmitAnswerRequest parsedData;
	parsedData.answer = answer;
	return parsedData;
}