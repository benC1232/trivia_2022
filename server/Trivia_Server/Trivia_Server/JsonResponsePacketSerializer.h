#pragma once
#include "json.hpp"
#include <string>
#include <vector>
#include<bitset>
#include <iomanip>
#include <sstream>
#define START_OF_JSON_SECTION 5

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
public:
	static std::vector<unsigned char> serializeLoginResponse(struct LoginResponse loginResponse);
	static std::vector<unsigned char> serializeSignupResponse(struct SignupResponse signupResponse);
	static std::vector<unsigned char> serializeErrorResponse(struct ErrorResponse errorResponse);
};