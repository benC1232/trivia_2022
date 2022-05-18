#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	data.id = this->rooms.size() + 1;
	Room room(data);
	room.addUser(user);
	this->rooms[data.id] = room;
}

void RoomManager::deleteRoom(int ID)
{
	this->rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(int id)
{
	return this->rooms[id].getIsActive();
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (auto it = this->rooms.begin(); it != this->rooms.end(); it++)
	{
		rooms.push_back(it->second.getData());
	}
	return rooms;
}