#pragma once
#include "IDatabase.h"
//I dont know why this works, but dont remove one of the maps because if you do the code wont run
#include <map>
#include <map>
#include <list>
#include <string>
class SqliteDataBase :
	public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	bool doesUserExist(std::string username);
	bool doesPasswordMatch(std::string username, std::string password);
	void addNewUser(std::string username, std::string password, std::string email);
	std::vector<Question> getQuestions(int numOfQuestions);
	float getPlayerAverageAnswerTime(std::string username);
	int getNumOfCorrectAnswers(std::string username);
	int getNumOfTotalAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);
	//why wasnt this in the uml?!?!?!?!?!
	std::map<std::string, int> getHighScore();
	void addStatistics(std::string username, int averageTime, int correctAnswers, int wrongAnswers);
private:
	sqlite3* _db;
	void createTables();
};
