#pragma once
#include <map>
#include <vector>
#include "JsonResponsePacketSerializer.h"
#include "LoggedUser.h"
#include "Question.h"

using GameData = struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount{};
	unsigned int wrongAnswerCount{};
	unsigned int averageAnswerTime{};
};

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
	int getNumOfPlayers() const;
	bool isInGame(LoggedUser user);

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};
