#pragma once
#include<iostream>
#include "IDatabase.h"
#include<map>
#include<vector>

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* db);
	~StatisticsManager();
	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(std::string username) const;

private:
	IDatabase* m_database;
};
