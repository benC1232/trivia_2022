#include "RoomManager.h"

RoomManager::RoomManager()
{
	this->rooms = new std::map<int, Room>();
}

RoomManager::~RoomManager()
{
	delete this->rooms;
}

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	data.id = this->rooms->size() + 1;
	Room room(data);
	room.addUser(user);
	this->rooms->insert({ data.id,room });
}

void RoomManager::deleteRoom(int id)
{
	this->rooms->erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return this->rooms->find(id)->second.getIsActive();
}

std::vector<Room> RoomManager::getRooms()
{
	std::vector<Room> rooms;
	for (auto it = this->rooms->begin(); it != this->rooms->end(); it++)
	{
		rooms.push_back(it->second.getData());
	}
	return rooms;
}