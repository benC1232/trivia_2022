#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin(), buffer.end());
	nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
	std::string username = jsonObject["username"];
	std::string password = jsonObject["password"];
	LoginRequest parsedData;
	parsedData.password = password;
	parsedData.username = username;
	return parsedData;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	std::string jsonString(buffer.begin(), buffer.end());
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