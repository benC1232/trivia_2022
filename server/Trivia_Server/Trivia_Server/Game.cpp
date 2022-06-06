#include "Game.h"

Game::Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players)
{
	this->m_questions = questions;
	this->m_players = players;
	for(auto p : this->m_players )
	{
		p.second.currentQuestion = this->m_questions[0];
	}
	

}

Question Game::getQuestionForUser(LoggedUser user)
{

	int idx;
	for (auto q : this->m_questions) {
		if(q.getQuestion()==this->m_players[user].currentQuestion.getQuestion()) {
			break;
		}
		idx++;
	}
	return this->m_questions[idx+1];
	
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
}

void Game::removePlayer(LoggedUser user)
{
	this->m_players.erase(user);
}

bool Game::operator==(const Game& other) const
{
	return this->m_questions == other.m_questions && this->m_players == other.m_players;
}
