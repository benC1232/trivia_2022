#include "StatisiticsManager.h"

StatisticsManager::StatisticsManager(IDatabase *db)
{
	this->m_database = db;
}

StatisticsManager::~StatisticsManager()
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	return std::vector<std::string>();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	return std::vector<std::string>();
}
