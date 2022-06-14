#include "RoomManager.h"

RoomManager::RoomManager()
{
	this->rooms = new std::map<int, Room*>();
}

RoomManager::~RoomManager()
{
	for (std::map<int, Room*>::iterator it = this->rooms->begin(); it != this->rooms->end(); ++it)
	{
		delete it->second;
	}
	delete this->rooms;
}
/*
* Adds a room to the manager
* input: user and data of the room
* output: id of the room
*/
int RoomManager::createRoom(LoggedUser user, RoomData data) const
{
	data.id = this->rooms->size() + 1;
	Room* room = new Room(data);
	room->addUser(user);
	this->rooms->insert({ data.id, room });
	return room->getData().id;
}
/*
* deletes room from the manager
* input: id of the room
* output: none
*/
void RoomManager::deleteRoom(int id) const
{
	delete this->rooms->find(id)->second;
	this->rooms->erase(id);
}
/*
* gets the room state from the manager
* input: id of the room
* output: state of the room
*/
unsigned int RoomManager::getRoomState(int id) const
{
	return this->rooms->find(id)->second->getIsActive();
}
/*
* getter for the rooms in the manager
* input: none
* output: rooms
*/
std::vector<Room> RoomManager::getRooms() const
{
	std::vector<Room> rooms;
	for (auto it = this->rooms->begin(); it != this->rooms->end(); ++it)
	{
		rooms.push_back(it->second->getData());
	}
	return rooms;
}
/*
* gets the room from the manager by id
* input: id of the room
* output: room
*/
Room* RoomManager::getRoom(int id) const
{
	return this->rooms->find(id)->second;
}