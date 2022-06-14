#include "Room.h"

Room::Room(RoomData data)
{
	this->m_metadata = data;
}
/*
* function adds a user to the room
* input: user to add
* output: none
*/
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
/*
* function removes a user from the room
* input: user to remove
* output: none
*/
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
/*
* getter function for the user vector
* input: none
* output: user vector
*/
std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> returnedValue;
	for (auto name : this->m_users)
	{
		returnedValue.push_back(name.getUsername());
	}
	return returnedValue;
}
/*
* getter function for the isactive field in the metadata
* input: none
* output: isactive field
*/
unsigned int Room::getIsActive() const
{
	return this->m_metadata.isActive;
}
/*
* getter function for the metadata
* input: none
* output: metadata
*/
RoomData Room::getData()
{
	return this->m_metadata;
}
/*
* getter function for the users
* input: none
* output: users
*/
std::vector<LoggedUser> Room::getAllUsersVector()
{
	return this->m_users;
}
/*
* setter function for the isactive field in the metadata
* input: isactive field
* output: none
*/
void Room::setIsActive(bool isActive)
{
	this->m_metadata.isActive = isActive;
}