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
		const std::string error = "too many players in room number : " + std::to_string(this->m_metadata.id);
		throw std::exception(error.c_str());
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
		const std::string error = "user not found in room number : " + std::to_string(this->m_metadata.id);
		throw std::exception(error.c_str());
	}
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> returnedValue;
	for (auto name : this->m_users)
	{
		returnedValue.push_back(name.getUsername());
	}
	return returnedValue;
}

unsigned int Room::getIsActive() const
{
	return this->m_metadata.isActive;
}

RoomData Room::getData()
{
	return this->m_metadata;
}

std::vector<LoggedUser> Room::getAllUsersVector()
{
	return this->m_users;
}

void Room::setIsActive(bool isActive)
{
	this->m_metadata.isActive = isActive;
}