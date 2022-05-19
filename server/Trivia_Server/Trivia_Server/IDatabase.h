#pragma once
#include <string>
#include "sqlite3.h"
#include <io.h>
#include <iostream>
#include <vector>
#include "Question.h"
class IDatabase
{
public:
	IDatabase() = default;
	//users function
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
	//question function
	virtual std::vector<Question> getQuestions(int numOfQuestions) = 0;
	//statistics function
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
private:
	virtual void createTables() = 0;
};