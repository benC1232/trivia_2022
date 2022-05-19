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
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
	
	

private:
	IDatabase* m_database;
};

