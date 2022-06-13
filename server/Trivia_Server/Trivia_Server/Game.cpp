#include "Game.h"

#include <algorithm>
#include <iostream>

/*
 * the constructor for the game class
 * input:questions(std::vector<Question>),players(std::map<LoggedUser, GameData>)
 */
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

/*
 * a function that returns the next question for a user - LoggedUser
 * input: user(LoggedUser)
 * output the next question in the question vector (Question)
 *
 */
Question Game::getQuestionForUser(LoggedUser user)
{
	Question q;
	q.setQuestion("");
	if (this->m_players.at(user).currentQuestion.getQuestion() == q.getQuestion()) {
		this->m_players.at(user).currentQuestion = this->m_questions.at(0);
		return this->m_questions[0];
	}
	int idx = 0;
	std::cout << "reached the loop somehow" << std::endl;
	for (auto q : this->m_questions) {
		if (q.getQuestion() == m_players.at(user).currentQuestion.getQuestion()) {
			break;
		}
		idx++;
	}
	if (idx == this->m_questions.size())
	{
		throw(std::exception("no more questions"));
	}
	this->m_players.at(user).currentQuestion = this->m_questions.at(idx + 1);
	return this->m_questions.at(idx + 1);
}


/*
 * a function that makes the user to submit his answer
 * input: user(LoggedUser), answer(std::string), time(int)
 * output: true if the answer is correct, false if not
 */
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
	this->m_players[user].averageAnswerTime = (((this->m_players[user].averageAnswerTime * (this->m_players[user].
		correctAnswerCount + this->m_players[user].wrongAnswerCount) - 1) + time) / (this->m_players[user].
			correctAnswerCount + this->m_players[user].wrongAnswerCount));
	return result;
}

/*
 * removes a player
 * input: user(LoggedUser)
 * output: none
 */
void Game::removePlayer(LoggedUser user)
{
	this->m_players.erase(user);
}

std::vector<PlayerResults> Game::getResults()
{
	auto output = std::vector<PlayerResults>();
	for (auto i = this->m_players.begin(); i != this->m_players.end(); ++i)
	{
		PlayerResults result;
		auto loggedUserName = i->first;
		result.username = loggedUserName.getUsername();
		result.correctAnswerCount = i->second.correctAnswerCount;
		result.wrongAnswerCount = i->second.wrongAnswerCount;
		result.averageAnswerTime = i->second.averageAnswerTime;
		output.push_back(result);
	}

	std::sort(output.begin(), output.end(), [](const PlayerResults& lhs, const PlayerResults& rhs)
		{
			return lhs.correctAnswerCount > rhs.correctAnswerCount;
		});
	return output;
}

//get the number of players in the game
int Game::getNumOfPlayers() const
{
	return this->m_players.size();
}

// returns true if the user is in the game
bool Game::isInGame(LoggedUser user)
{
	return this->m_players.find(user) != this->m_players.end();
}