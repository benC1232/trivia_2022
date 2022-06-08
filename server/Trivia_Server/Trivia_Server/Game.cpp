#include "Game.h"


Game::Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players)
{
	Question q;
	q.setQuestion("Err q");

	this->m_questions = questions;
	this->m_players = players;
	for (auto p : this->m_players)
	{
		p.second.currentQuestion = q;
	}
}

Question Game::getQuestionForUser(LoggedUser user)
{
	Question q;
	q.setQuestion("Err q");
	if (this->m_players[user].currentQuestion.getQuestion() == q.getQuestion()) {
		this->m_players[user].currentQuestion = this->m_questions[0];
		return this->m_questions[0];
	}
	int idx = 0;
	for (auto q : this->m_questions) {
		if (q.getQuestion() == this->m_players[user].currentQuestion.getQuestion()) {
			break;
		}
		idx++;
	}
	this->m_players[user].currentQuestion = this->m_questions[idx+1];
	return this->m_questions[idx + 1];
}

bool Game::submitAnswer(LoggedUser user, std::string answer, int time)
{
	bool result;
	if (this->m_players[user].currentQuestion.getCorrectAnswer() == answer)
	{
		this->m_players[user].correctAnswerCount++;
		result = true;
	}
	else
	{
		this->m_players[user].wrongAnswerCount++;
		result = false;
	}
	this->m_players[user].averageAnswerTime = (((this->m_players[user].averageAnswerTime * (this->m_players[user].correctAnswerCount + this->m_players[user].wrongAnswerCount) - 1) + time) / (this->m_players[user].correctAnswerCount + this->m_players[user].wrongAnswerCount));
	return result;
}

void Game::removePlayer(LoggedUser user)
{
	this->m_players.erase(user);
}

std::vector<PlayerResults> Game::getResults()
{
	auto output = std::vector<PlayerResults>();
	for (auto i = this->m_players.begin(); i != this->m_players.end(); ++i) {
		PlayerResults result;
		auto loggedUserName = i->first;
		result.username = loggedUserName.getUsername();
		result.correctAnswerCount = i->second.correctAnswerCount;
		result.wrongAnswerCount = i->second.wrongAnswerCount;
		result.averageAnswerTime = i->second.averageAnswerTime;
		output.push_back(result);
	}
	return output;
}

int Game::getNumOfPlayers()
{
	return this->m_players.size();
}

bool Game::isInGame(LoggedUser user)
{
	return this->m_players.find(user) != this->m_players.end();
}

