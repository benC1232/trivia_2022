#include "StatisticsManager.h"

/*
 * statistics manager constructor
 * input: db (IDatabase*)
 */
StatisticsManager::StatisticsManager(IDatabase* db) : m_database(db) {}

StatisticsManager::~StatisticsManager()
{
	delete m_database;
}

/*
 * a function to get the high score of the game by accessing the database to find the players with the highest score
 * input: none
 * output: vector of strings containing the name and score of the players with the highest score (std::vector<std::string>)
 */
std::vector<std::string> StatisticsManager::getHighScore()
{
	std::vector<std::string> stats;
	const auto res = this->m_database->getHighScore();
	for (auto& row : res)
	{
		stats.push_back(row.first + ": " + std::to_string(row.second));
	}
	return stats;
}

/*
 * a function to get the personal statistics of a certain player by accessing the database to find the players with the highest score
 * the statistics that are returned are: number of correct answers, number of total answers, number of games played, average answer time
 * input: username (std::string)
 * output: vector of strings containing the name and score of the players with the highest score (std::vector<std::string>)
 */

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> stats;
	stats.push_back("Number Of Correct Answers: " + std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back("Number Of Total Answers: " + std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back("Number Of Games Played: " + std::to_string(m_database->getNumOfPlayerGames(username)));
	stats.push_back("Average Answer Time: " + std::to_string(m_database->getPlayerAverageAnswerTime(username)));
	return stats;
}