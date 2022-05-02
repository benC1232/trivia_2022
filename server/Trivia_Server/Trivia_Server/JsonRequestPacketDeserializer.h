#pragma once
#include "json.hpp"
#include <string>
#include <vector>
//structs will be here:

//login request struct
struct LoginRequest
{
	std::string password;
	std::string username;
};
//signup request struct
struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};
class JsonRequestPacketDeserializer
{
public:
	static struct LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static struct SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
};
