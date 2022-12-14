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
	const std::string username = jsonObject["username"];
	const std::string password = jsonObject["password"];
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
	const std::string username = jsonObject["username"];
	const std::string password = jsonObject["password"];
	const std::string email = jsonObject["email"];
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
	const std::string roomId = jsonObject["roomId"];
	GetPlayersInRoomRequest parsedData;
	try
	{
		parsedData.roomId = std::atoi(roomId.c_str());
	}
	catch (...)
	{
		throw std::exception("roomId is not a number");
	}
	return parsedData;
}
/*
function parses the json part of a packet and returns the content of the fields
input: vector of unsigned chars (bytes) representing the json string
output: the content of the fields in the json
*/
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	const std::string roomId = jsonObject["roomId"];
	JoinRoomRequest parsedData;
	try
	{
		parsedData.roomId = std::atoi(roomId.c_str());
	}
	catch (...)
	{
		throw std::exception("roomId is not a number");
	}
	return parsedData;
}
/*
function parses the json part of a packet and returns the content of the fields
input: vector of unsigned chars (bytes) representing the json string
output: the content of the fields in the json
*/
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	const std::string roomName = jsonObject["roomName"];
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
/*
function parses the json part of a packet and returns the content of the fields
input: vector of unsigned chars (bytes) representing the json string
output: the content of the fields in the json
*/
SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	const std::string answer = jsonObject["answer"];
	int responseTime = jsonObject["responseTime"];
	SubmitAnswerRequest parsedData;
	try
	{
		parsedData.answer = answer;
		parsedData.responseTime = responseTime;
	}
	catch (...)
	{
		throw std::exception("responseTime is not a number");
	}
	return parsedData;
}
/*
function parses the json part of a packet and returns the content of the fields
input: vector of unsigned chars (bytes) representing the json string
output: the content of the fields in the json
*/
AddQuestionRequest JsonRequestPacketDeserializer::deserializeAddQuestionRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin() + JSON_OFFSET, buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string question = jsonObject["question"];
	std::string correctAnswer = jsonObject["correctAnswer"];
	std::string wrongAnswer1 = jsonObject["wrongAnswer1"];
	std::string wrongAnswer2 = jsonObject["wrongAnswer2"];
	std::string wrongAnswer3 = jsonObject["wrongAnswer3"];
	AddQuestionRequest parsedData;
	parsedData.question = question;
	parsedData.correctAnswer = correctAnswer;
	parsedData.wrongAnswer1 = wrongAnswer1;
	parsedData.wrongAnswer2 = wrongAnswer2;
	parsedData.wrongAnswer3 = wrongAnswer3;
	return parsedData;
}