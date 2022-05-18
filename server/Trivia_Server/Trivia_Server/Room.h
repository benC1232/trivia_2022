#pragma once
#include <string>
#include <vector>
#include "LoggedUser.h"
//room data struct
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	bool isActive;
};
class Room
{
public:
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	std::vector<std::string> getAllUsers();
private:
	RoomData m_metaData;
	std::vector<LoggedUser> m_users;
};
