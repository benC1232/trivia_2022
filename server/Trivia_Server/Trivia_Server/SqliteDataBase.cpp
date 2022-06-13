#include "SqliteDataBase.h"
#include <io.h>
#include <iostream>
#include <ostream>

SqliteDataBase::SqliteDataBase()
{
	const std::string dbFileName = "Trivia.sqlite";
	const int file_exist = _access(dbFileName.c_str(), 0);
	const int result = sqlite3_open(dbFileName.c_str(), &this->_db);
	if (result != SQLITE_OK)
	{
		this->_db = nullptr;
		throw std::exception("Failed to open DB");
	}
	if (file_exist != 0)
	{
		this->createTables();
	}
}

SqliteDataBase::~SqliteDataBase()
{
	sqlite3_close(this->_db);
	delete this->_db;
}

int userExistCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<int*>(data);
	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] == std::string("username"))
		{
			*static_cast<int*>(data) = 1;
		}
	}
	return 0;
}

int passwordMatchCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<int*>(data);
	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] == std::string("username"))
		{
			*static_cast<int*>(data) = 1;
		}
		else if (azColName[i] == std::string("password"))
		{
			*static_cast<int*>(data) = 1;
		}
	}
	return 0;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	int exists = 0;
	char* errMessage = nullptr;
	const std::string query = "SELECT * FROM USERS WHERE username = '" + username + "';";
	const int result = sqlite3_exec(this->_db, query.c_str(), userExistCallback, &exists, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return exists == 1;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	int exists = 0;
	char* errMessage = nullptr;
	const std::string query = "SELECT * FROM USERS WHERE username = '" + username + "' AND password = '" + password +
		"';";
	const int result = sqlite3_exec(this->_db, query.c_str(), passwordMatchCallback, &exists, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return exists == 1;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	char* errMessage = nullptr;
	std::string query = "INSERT INTO Users (username, password, email) VALUES ('" + username + "', '" + password +
		"', '" + email + "')";
	const char* sqlStatement = query.c_str();
	int result = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	errMessage = nullptr;
	query = "INSERT INTO statistics (username, averagetime, correctanswers, wronganswers, gamesnum) VALUES ('" +
		username + "', 0, 0, 0, 0)";
	sqlStatement = query.c_str();
	result = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
}

int questionsCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<std::vector<Question>*>(data);
	Question question;
	std::vector<std::string> incorrectanswers;
	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] == std::string("question"))
		{
			question.setQuestion(argv[i]);
		}
		else if (azColName[i] == std::string("correctanswer"))
		{
			question.setCorrectAnswer(argv[i]);
		}
		else if (azColName[i] == std::string("wronganswer1") || azColName[i] == std::string("wronganswer2") || azColName
			[i] == std::string("wronganswer3"))
		{
			incorrectanswers.push_back(argv[i]);
		}
	}
	question.setIncorrectAnswers(incorrectanswers);
	static_cast<std::vector<Question>*>(data)->push_back(question);
	return 0;
}

std::vector<Question> SqliteDataBase::getQuestions(int numOfQuestions)
{
	char* errMessage = nullptr;
	std::cout << "numOfQuestions: " << numOfQuestions << std::endl;
	const std::string query = "SELECT * FROM Questions ORDER BY RANDOM() LIMIT " + std::to_string(numOfQuestions) + ";";
	const char* sqlStatement = query.c_str();
	std::vector<Question> questions;
	const int result = sqlite3_exec(this->_db, sqlStatement, questionsCallback, &questions, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	std::cout << "got questions" << std::endl;
	return questions;
}

int averageTimeCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<float*>(data);
	if (argc == 0)
	{
		*static_cast<float*>(data) = 0;
	}
	else
	{
		*static_cast<float*>(data) = atof(argv[0]);
	}
	return 0;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	const std::string query = "SELECT averagetime FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	float result = 0;
	const int res = sqlite3_exec(this->_db, query.c_str(), averageTimeCallback, &result, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return result;
}

int correctAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<int*>(data);
	if (argc == 0)
	{
		*static_cast<int*>(data) = 0;
	}
	else
	{
		*static_cast<int*>(data) = std::atoi(argv[0]);
	}
	return 0;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	const std::string query = "SELECT correctanswers FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	int result = 0;
	const int res = sqlite3_exec(this->_db, query.c_str(), correctAnswersCallback, &result, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return result;
}

int totalAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<int*>(data);
	if (argc == 0)
	{
		*static_cast<int*>(data) = 0;
	}
	else
	{
		*static_cast<int*>(data) = std::atoi(argv[0]);
	}
	return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	const std::string query = "SELECT correctanswers+wronganswers FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	int result = 0;
	const int res = sqlite3_exec(this->_db, query.c_str(), totalAnswersCallback, &result, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return result;
}

int gameAmountCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<int*>(data);
	if (argc == 0)
	{
		*static_cast<int*>(data) = 0;
	}
	else
	{
		*static_cast<int*>(data) = std::atoi(argv[0]);
	}
	return 0;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	const std::string query = "SELECT gamesnum FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	int result = 0;
	const int res = sqlite3_exec(this->_db, query.c_str(), gameAmountCallback, &result, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return result;
}

int highScoreCallback(void* data, int argc, char** argv, char** azColName)
{
	data = static_cast<std::map<std::string, int>*>(data);
	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] == std::string("username"))
		{
			static_cast<std::map<std::string, int>*>(data)->insert(
				std::pair<std::string, int>(argv[i], std::atoi(argv[i + 1]) * 5));
		}
	}
	return 0;
}

std::map<std::string, int> SqliteDataBase::getHighScore()
{
	std::map<std::string, int> highScore;
	char* errMessage = nullptr;
	const std::string query = "SELECT username, correctanswers FROM statistics ORDER BY correctanswers DESC LIMIT 5;";
	const char* sqlStatement = query.c_str();
	const int result = sqlite3_exec(this->_db, sqlStatement, highScoreCallback, &highScore, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	return highScore;
}

void SqliteDataBase::addStatistics(std::string username, int averageTime, int correctAnswers, int wrongAnswers)
{
	char* errMessage = nullptr;
	const std::string query = "UPDATE statistics "
		"SET averagetime = (averagetime + " + std::to_string(averageTime) + ") / 2, "
		"correctanswers = correctanswers + " + std::to_string(correctAnswers) + ","
		"wronganswers = wronganswers + " + std::to_string(wrongAnswers) + ","
		"gamesnum = gamesnum + 1 "
		"WHERE username = '" + username + "';";
	const char* sqlStatement = query.c_str();
	const int result = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
}

void SqliteDataBase::addQuestion(Question question)
{
	char* errMessage = nullptr;
	const std::string query =
		"INSERT INTO questions (question, correctanswer, wronganswer1,wronganswer2,wronganswer3) VALUES ('" + question.
		getQuestion() + "','" + question.getCorrectAnswer() + "','" + question.getIncorrectAnswers()[0] + "','" +
		question.getIncorrectAnswers()[1] + "','" + question.getIncorrectAnswers()[2] + "');";
	const char* sqlStatement = query.c_str();
	const int result = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
}

void SqliteDataBase::createTables()
{
	std::cout << "creating tables" << std::endl;
	char* errMessage = nullptr;
	//creating users table
	const char* sqlStatement = "CREATE TABLE IF NOT EXISTS USERS ( "
		"username TEXT PRIMARY KEY,"
		"password TEXT NOT NULL,"
		"email TEXT NOT NULL UNIQUE"
		"); ";
	int res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	//creating question table
	sqlStatement = "CREATE TABLE IF NOT EXISTS questions"
		"("
		"questionid    INTEGER PRIMARY KEY AUTOINCREMENT, "
		"question      TEXT NOT NULL,"
		"correctanswer TEXT NOT NULL, "
		"wronganswer1  TEXT NOT NULL,"
		"wronganswer2  TEXT NOT NULL,"
		"wronganswer3  TEXT NOT NULL"
		");";
	res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
	//creating statistics table
	sqlStatement = "CREATE TABLE IF NOT EXISTS statistics"
		"("
		"username       TEXT PRIMARY KEY, "
		"averagetime    FLOAT NOT NULL,"
		"correctanswers INTEGER NOT NULL, "
		"wronganswers   INTEGER NOT NULL,"
		"gamesnum     INTEGER NOT NULL"
		"); ";
	res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(errMessage);
	}
}