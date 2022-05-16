#pragma once
#include "IDatabase.h"
#include<vector>
#include<stdio.h>

class StatisticsManager {
public:
	StatisticsManager(IDatabase* db);
	~StatisticsManager();
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
private:
	IDatabase* m_database;


};