#include "GameManager.h"



GameManager::GameManager(IDatabase* database, std::vector<Game> games)
{
	this->m_database = database;
	this->m_games = games;
}

GameManager::~GameManager()
{
	delete this->m_database;
}

Game GameManager::createGame(Room room)
{
	std::map<LoggedUser, GameData>* players = new std::map<LoggedUser, GameData>();
	for (auto user : room.getAllUsersVector()) {
		GameData gd = {
			Question(),
			0,
			0,
			0
		};
		players->insert(std::pair<LoggedUser,GameData>(user,gd));
	
	}
	auto g = Game(this->m_database->getQuestions(room.getData().numOfQuestionsInGame), *players);
	this->m_games.push_back(g);
	return g;
}

void GameManager::deleteGame(Game game)
{
	//remove game from vector
	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++) {
		if (*it == game) {
			this->m_games.erase(it);
			break;
		}
	}
}
