#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db): m_database(db) {}

StatisticsManager::~StatisticsManager()
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	std::vector<std::string> stats;
	auto res = this->m_database->getHighScore();
	for (auto& row : res)
	{
		stats.push_back(row.first+": "+std::to_string(row.second));
	}
	return stats;

}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> stats;
	stats.push_back("Number Of Correct Answers: " + std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back("Number Of Total Answers: " + std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back("Number Of Games Played: " + std::to_string(m_database->getNumOfPlayerGames(username)));
	stats.push_back("Average Answer Time: " + std::to_string(m_database->getPlayerAverageAnswerTime(username)));
	return stats;
		
}
