#pragma once
#include "json.hpp"
#include <string>
#include <vector>
#include<bitset>

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct ErrorResponse {
	std::string message;
};

class JsonResponsePacketSerializer {
public :
	std::vector<unsigned char> serializeLoginResponse(struct LoginResponse loginResponse);
	std::vector<unsigned char> serializeSignupResponse(struct SignupResponse signupResponse);
	std::vector<unsigned char> serializeErrorResponse(struct ErrorResponse errorResponse);
};