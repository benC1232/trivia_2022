#pragma once
#include <map>
#include "Room.h"
#include "LoggedUser.h"
class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	int createRoom(LoggedUser user, RoomData data) const;
	void deleteRoom(int id) const;
	unsigned int getRoomState(int id) const;
	std::vector<Room> getRooms() const;
	Room* getRoom(int id) const;

private:
	std::map<int, Room*>* rooms;
};
