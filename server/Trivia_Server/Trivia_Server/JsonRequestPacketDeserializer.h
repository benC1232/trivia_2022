#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#define JSON_OFFSET 5
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

//get players in room request struct
struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

//join room request struct
struct JoinRoomRequest
{
	unsigned int roomId;
};

//add question request struct
struct AddQuestionRequest
{
	std::string question;
	std::string correctAnswer;
	std::string wrongAnswer1;
	std::string wrongAnswer2;
	std::string wrongAnswer3;
};

//create room request struct
struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int answerTimeout;
	unsigned int questionCount;
};

struct SubmitAnswerRequest
{
	std::string answer;
	unsigned int responseTime;
};

class JsonRequestPacketDeserializer
{
public:
	static struct LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static struct SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
	static struct GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer);
	static struct JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static struct CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer);
	static struct SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<unsigned char> buffer);
	static struct AddQuestionRequest deserializeAddQuestionRequest(std::vector<unsigned char> buffer);
};
