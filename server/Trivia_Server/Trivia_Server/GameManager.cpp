#include "GameManager.h"
#include <algorithm>


/*
 * the constructor of the gameManager
 * input: database (IDatabase*)
 */
GameManager::GameManager(IDatabase* database)
{
	this->m_database = database;
	this->m_games = std::vector<Game*>();
}



GameManager::~GameManager()
{
	delete this->m_database;  
}

/*
 * a function that creates a game from a room and adds it to the room vector
 * input: room (Room)
 * output: game (Game*)
 */
Game* GameManager::createGame(Room room)
{
	auto players = new std::map<LoggedUser, GameData>();
	for (auto user : room.getAllUsersVector()) {
		GameData gd;
		gd.currentQuestion = Question();
		gd.correctAnswerCount = 0;
		gd.wrongAnswerCount = 0;
		gd.averageAnswerTime = 0;
		players->insert(std::pair<LoggedUser, GameData>(user, gd));
	}
	auto g = new Game(this->m_database->getQuestions(room.getData().numOfQuestionsInGame), *players);
	this->m_games.push_back(g);
	return g;
}

/*
 * a function that deletes a game from the vector by its pointer
 * input: game (Game*)
 * output: none
 */
void GameManager::deleteGame(Game* game)
{
	auto it = std::find(m_games.begin(), m_games.end(), game);
	if (it != m_games.end()) {
		m_games.erase(it);
	}
}

/*
 * a function that gets a game by the user that is playing in it
 * input: user (LoggedUser)
 * output: game (Game*)
 */
Game* GameManager::getGame(LoggedUser user) const
{
	for (auto game : m_games) {
		if (game->isInGame(user)){
			return game;
		}
	}
	return nullptr;

}

