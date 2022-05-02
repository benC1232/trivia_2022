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
bool IDatabase::doesUserExist(std::string username)
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

bool IDatabase::doesPasswordMatch(std::string username, std::string password)
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

void IDatabase::addNewUser(std::string username, std::string password, std::string email)
{
	char* errMessage = nullptr;
	std::string query = "INSERT INTO Users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "')";
	const char* sqlStatement = query.c_str();
	int result = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK) {
		throw std::exception(errMessage);
	}
}

void IDatabase::createTables()
{
	std::cout << "creating tables" << std::endl;
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