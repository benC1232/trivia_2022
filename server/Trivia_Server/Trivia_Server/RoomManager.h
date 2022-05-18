#pragma once
#include <map>
#include "Room.h"
#include "LoggedUser.h"
class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();

private:
	std::map<int, Room> rooms;
};
