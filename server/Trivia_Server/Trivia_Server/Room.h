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
	unsigned int isActive;
};
class Room
{
public:
	Room() = default;
	Room(RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
