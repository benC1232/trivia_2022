#include "JsonResponsePacketSerializer.h"

//the first byte of the vector is the msg type
//1 - login, 2 - signup, 3 -error
//the next four bytes are the size of the struct fields in bytes


std::vector<unsigned char> intToByteVector(int num){
	std::vector<unsigned char> buffer(4);
	for (int i = 0; i < 4; i++) buffer[3 - i] = (num << i * 8);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse loginResponse)
{
    std::vector<unsigned char> buffer;
	buffer.push_back(1);
	nlohmann::json jsonResponse = {{"status", ""+loginResponse.status}};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for(unsigned char c: jsonString) buffer.push_back(c);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse signupResponse)
{
    std::vector<unsigned char> buffer;
	buffer.push_back(2);
	nlohmann::json jsonResponse = {{"status", ""+signupResponse.status}};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for(unsigned char c: jsonString) buffer.push_back(c);
	return buffer;
	
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse errorResponse)
{
    std::vector<unsigned char> buffer;
	buffer.push_back(3);
	nlohmann::json jsonResponse = {{"message","" + errorResponse.message}};
	std::string jsonString = nlohmann::to_string(jsonResponse);
	std::vector<unsigned char> lenBuff = intToByteVector(jsonString.length());
	buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
	for(unsigned char c: jsonString) buffer.push_back(c);
	return buffer;
}


