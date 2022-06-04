#pragma once
#include <map>
#include "Room.h"
#include "LoggedUser.h"
class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	int createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<Room> getRooms();
	Room* getRoom(int id);

private:
	std::map<int, Room*>* rooms;
};
