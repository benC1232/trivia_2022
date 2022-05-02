#include "IDatabase.h"
IDatabase::IDatabase()
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

IDatabase::~IDatabase()
{
	delete this->_db;
}

bool IDatabase::doesUserExist(std::string username)
{
	return false;
}

bool IDatabase::doesPasswordMatch(std::string username, std::string password)
{
	return false;
}

void IDatabase::addNewUser(std::string username, std::string password, std::string email)
{
	char* errMessage = nullptr;
	std::string query = "INSERT INTO Users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "')";
	const char* sqlStatement = query.c_str();
	int res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
}

void IDatabase::createTables()
{
	char* errMessage = nullptr;
	const char* sqlStatement = "CREATE TABLE IF NOT EXISTS USERS ( "
		"username TEXT PRIMARY KEY,"
		"password TEXT NOT NULL,"
		"email TEXT NOT NULL UNIQUE"
		"); ";
	int res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK) {
		throw std::exception(errMessage);
	}
}