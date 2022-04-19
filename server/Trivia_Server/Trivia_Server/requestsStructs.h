#pragma once
#include <string>
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