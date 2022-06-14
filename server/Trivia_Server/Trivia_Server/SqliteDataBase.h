#pragma once
#include "IDatabase.h"
//I don't know why this works, but dont remove one of the maps because if you do the code wont run
#include <map>
#include <map>
#include <string>

#include "sqlite3.h"

class SqliteDataBase :
	public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase() override;
	bool doesUserExist(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string email) override;
	std::vector<Question> getQuestions(int numOfQuestions) override;
	float getPlayerAverageAnswerTime(std::string username) override;
	int getNumOfCorrectAnswers(std::string username) override;
	int getNumOfTotalAnswers(std::string username) override;
	int getNumOfPlayerGames(std::string username) override;
	//why wasn't this in the uml?!?!?!?!?!
	std::map<std::string, int> getHighScore() override;
	void addStatistics(std::string username, int averageTime, int correctAnswers, int wrongAnswers) override;
	void addQuestion(Question question) override;
private:
	sqlite3* _db;
	void createTables() override;
};
