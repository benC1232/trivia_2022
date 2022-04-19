#pragma once
#include "json.hpp"
#include <vector>
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned int> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned int> buffer);
};
//structs will be here:

//login request struct
typedef struct LoginRequest
{
	std::string password;
	std::string username;
}LoginRequest;
//signup request struct
typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}SignupRequest;