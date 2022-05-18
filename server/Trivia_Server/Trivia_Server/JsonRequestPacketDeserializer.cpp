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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
	return GetPlayersInRoomRequest();
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	return JoinRoomRequest();
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	return CreateRoomRequest();
}