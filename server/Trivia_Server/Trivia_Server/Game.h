#pragma once
#include "Question.h"
#include "IDatabase.h"
#include "LoggedUser.h"
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
	void submitAnswer(LoggedUser user, std::string answer);
	void removePlayer(LoggedUser user);
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	
	
};

