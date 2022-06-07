#include "GameManager.h"
#include <algorithm>

GameManager::GameManager(IDatabase* database)
{
	this->m_database = database;
	this->m_games = std::vector<Game*>();
}


GameManager::~GameManager()
{
	delete this->m_database;
}

Game* GameManager::createGame(Room room)
{
	std::map<LoggedUser, GameData>* players = new std::map<LoggedUser, GameData>();
	for (auto user : room.getAllUsersVector()) {
		GameData gd = {
			Question(),
			0,
			0,
			0
		};
		players->insert(std::pair<LoggedUser, GameData>(user, gd));
	}
	auto g = new Game(this->m_database->getQuestions(room.getData().numOfQuestionsInGame), *players);
	this->m_games.push_back(g);
	return g;
}

void GameManager::deleteGame(Game* game)
{
	auto it = std::find(m_games.begin(), m_games.end(), game);
	if (it != m_games.end()) {
		m_games.erase(it);
	}
}

Game* GameManager::getGame(LoggedUser user)
{
	for (auto game : m_games) {
		if (game->isInGame(user)){
			return game;
		}
	}
	return nullptr;

}
