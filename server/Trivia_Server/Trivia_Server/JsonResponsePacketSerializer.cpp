#include "JsonResponsePacketSerializer.h"

//the first byte of the vector is the msg type
//1 - login, 2 - signup, 3 -error
//the next four bytes are the size of the struct fields in bytes

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse loginResponse)
{
    std::vector<unsigned char> buffer;
	buffer.push_back(1);
	nlohmann::json jsonResponse = {{"status", ""+loginResponse.status}};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::string s = std::bitset<4>(jsonString.length()).to_string();
	if (s.length() > 4) throw std::overflow_error("The length of the json is greater than 16");
	for (int i = 1; i < 5; i++) buffer.push_back(s[i - 1]);
	for(unsigned char c: jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse signupResponse)
{
    std::vector<unsigned char> buffer;
	buffer.push_back(2);
	nlohmann::json jsonResponse = {{"status", ""+signupResponse.status}};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::string s = std::bitset<4>(jsonString.length()).to_string();
	if (s.length() > 4) throw std::overflow_error("The length of the json is greater than 16");
	for (int i = 1; i < 5; i++) buffer.push_back(s[i - 1]);
	for(unsigned char c: jsonString) buffer.push_back(c);
	return buffer;
	
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse errorResponse)
{
    std::vector<unsigned char> buffer;
	buffer.push_back(3);
	nlohmann::json jsonResponse = {{"message","" + errorResponse.message}};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::string s = std::bitset<4>(jsonString.length()).to_string();
	if (s.length() > 4) throw std::overflow_error("The length of the json is greater than 16");
	for (int i = 1; i < 5; i++) buffer.push_back(s[i - 1]);
	for(unsigned char c: jsonString) buffer.push_back(c);
	return buffer;
}
