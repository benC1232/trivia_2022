#pragma once
#include <vector>
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"

class Game;

class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game*> m_games;
public:
	GameManager() = default;
	~GameManager();
	GameManager(IDatabase* database);
	Game* getGame(LoggedUser user);
	Game* createGame(Room room);
	void deleteGame(Game* game);
};
