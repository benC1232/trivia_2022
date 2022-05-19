#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
	std::string dbFileName = "Trivia.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int result = sqlite3_open(dbFileName.c_str(), &this->_db);
	if (result != SQLITE_OK) {
		this->_db = nullptr;
		throw std::exception("Failed to open DB");
	}
	if (file_exist != 0) {
		this->createTables();
	}
}

SqliteDataBase::~SqliteDataBase()
{
	delete this->_db;
}
int userExistCallback(void* data, int argc, char** argv, char** azColName)
{
	//cast data to bool
	data = (bool*)data;
	if (argc == 0)
	{
		*(bool*)data = false;
	}
	else
	{
		*(bool*)data = true;
	}
	return 0;
}
int passwordMatchCallback(void* data, int argc, char** argv, char** azColName)
{
	//cast data to bool
	data = (bool*)data;
	if (argc == 0)
	{
		*(bool*)data = false;
	}
	else
	{
		*(bool*)data = true;
	}
	return 0;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	bool exists;
	char* errMessage = nullptr;
	std::string query = "SELECT * FROM USERS WHERE username = '" + username + "';";
	int result = sqlite3_exec(this->_db, query.c_str(), userExistCallback, &exists, &errMessage);
	if (result != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return exists;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	bool exists;
	char* errMessage = nullptr;
	std::string query = "SELECT * FROM USERS WHERE username = '" + username + "' AND password = '" + password + "';";
	int result = sqlite3_exec(this->_db, query.c_str(), passwordMatchCallback, &exists, &errMessage);
	if (result != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return exists;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	char* errMessage = nullptr;
	std::string query = "INSERT INTO Users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "')";
	const char* sqlStatement = query.c_str();
	int result = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK) {
		throw std::exception(errMessage);
	}
}
int questionsCallback(void* data, int argc, char** argv, char** azColName)
{
	data = (std::vector<Question>*)data;
}
//
std::vector<Question> SqliteDataBase::getQuestions(int numOfQuestions)
{
	char* errMessage = nullptr;
	std::string query = "SELECT * FROM Questions ORDER BY RANDOM() LIMIT " + std::to_string(numOfQuestions) + ";";
	const char* sqlStatement = query.c_str();
	std::vector<Question> questions;
	int result = sqlite3_exec(this->_db, sqlStatement, questionsCallback, questions, &errMessage);
	if (result != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return questions;
}

int averageTimeCallback(void* data, int argc, char** argv, char** azColName)
{
	data = (float*)data;
	if (argc == 0)
	{
		*(float*)data = 0;
	}
	else
	{
		*(float*)data = atof(argv[0]);
	}
	return 0;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	std::string query = "SELECT averagetime FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	float result = 0;
	int res = sqlite3_exec(this->_db, query.c_str(), averageTimeCallback, &result, &errMessage);
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return result;
}
int correctAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	data = (int*)data;
	if (argc == 0)
	{
		*(int*)data = 0;
	}
	else
	{
		*(int*)data = atoi(argv[0]);
	}
	return 0;
}
int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	std::string query = "SELECT correctanswers FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	int result = 0;
	int res = sqlite3_exec(this->_db, query.c_str(), correctAnswersCallback, &result, &errMessage);
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return result;
}
int totalAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	data = (int*)data;
	if (argc == 0)
	{
		*(int*)data = 0;
	}
	else
	{
		*(int*)data = atoi(argv[0]);
	}
	return 0;
}
int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	std::string query = "SELECT correctanswers+incorrectanswers FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	int result = 0;
	int res = sqlite3_exec(this->_db, query.c_str(), totalAnswersCallback, &result, &errMessage);
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return result;
}
int gameAmountCallback(void* data, int argc, char** argv, char** azColName)
{
	data = (int*)data;
	if (argc == 0)
	{
		*(int*)data = 0;
	}
	else
	{
		*(int*)data = atoi(argv[0]);
	}
	return 0;
}
int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	std::string query = "SELECT gamesnum FROM statistics WHERE username = '" + username + "';";
	char* errMessage = nullptr;
	int result = 0;
	int res = sqlite3_exec(this->_db, query.c_str(), gameAmountCallback, &result, &errMessage);
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
	return result;
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
	if (res != SQLITE_OK) {
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
	if (res != SQLITE_OK) {
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
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
}