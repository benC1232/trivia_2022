#include "Game.h"

Game::Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players)
{
	this->m_questions = questions;
	this->m_players = players;

}

Question Game::getQuestionForUser(LoggedUser user)
{
	return m_players[user].currentQuestion;
}

void Game::submitAnswer(LoggedUser user, std::string answer)
{
	if(this->m_players[user].currentQuestion.getCorrectAnswer() == answer)
	{
		this->m_players[user].correctAnswerCount++;
	}
	else
	{
		this->m_players[user].wrongAnswerCount++;
	}
	//time idk
	
	
	
}

void Game::removePlayer(LoggedUser user)
{
	this->m_players.erase(user);
}
