#pragma once
#include "IDatabase.h"
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
	int getNumOfIncorrectAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);
private:
	sqlite3* _db;
	void createTables();
};
