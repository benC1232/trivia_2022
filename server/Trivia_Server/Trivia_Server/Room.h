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
	Room() = default;
	Room(RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	unsigned int getIsActive();
	RoomData getData();
	std::vector<LoggedUser> getAllUsersVector();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
