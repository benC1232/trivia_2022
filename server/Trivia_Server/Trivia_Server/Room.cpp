#include "Room.h"

Room::Room(RoomData data)
{
	this->m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	if (this->m_users.size() < this->m_metadata.maxPlayers)
	{
		this->m_users.push_back(user);
	}
	else
	{
		throw std::exception("too many players in room number:" + this->m_metadata.id);
	}
}

void Room::removeUser(LoggedUser user)
{
	int flag = 0;
	//find user in vector
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == user.getUsername())
		{
			this->m_users.erase(this->m_users.begin() + i);
			flag++;
			break;
		}
	}
	if (flag != 1)
	{
		throw std::exception("user not found in room number:" + this->m_metadata.id);
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> returnedValue;
	for (auto name : this->m_users)
	{
		returnedValue.push_back(name.getUsername());
	}
	return returnedValue;
}