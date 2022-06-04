#include "RoomManager.h"

RoomManager::RoomManager()
{
	this->rooms = new std::map<int, Room*>();
}

RoomManager::~RoomManager()
{
	std::map<int, Room*>::iterator it;
	for (it = this->rooms->begin(); it != this->rooms->end(); it++)
	{
		delete it->second;
	}
	delete this->rooms;
}

int RoomManager::createRoom(LoggedUser user, RoomData data)
{
	data.id = this->rooms->size() + 1;
	Room* room = new Room(data);
	room->addUser(user);
	this->rooms->insert({ data.id,room });
	return room->getData().id;
}

void RoomManager::deleteRoom(int id)
{
	delete this->rooms->find(id)->second;
	this->rooms->erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return this->rooms->find(id)->second->getIsActive();
}

std::vector<Room> RoomManager::getRooms()
{
	std::vector<Room> rooms;
	for (auto it = this->rooms->begin(); it != this->rooms->end(); it++)
	{
		rooms.push_back(it->second->getData());
	}
	return rooms;
}

Room* RoomManager::getRoom(int id)
{
	return this->rooms->find(id)->second;
}