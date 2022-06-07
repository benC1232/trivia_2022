#pragma once
#include <chrono>
#include "Question.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
#include <vector>
#include <map>

typedef struct GameData {
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} GameData;

class Game
{
public:
	Game() = default;
	Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players);
	~Game() = default;
	Question getQuestionForUser(LoggedUser user);
	bool submitAnswer(LoggedUser user, std::string answer, int time);
	void removePlayer(LoggedUser user);
	std::vector<PlayerResults> getResults();
	int getNumOfPlayers();

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	//start time of the game
};
