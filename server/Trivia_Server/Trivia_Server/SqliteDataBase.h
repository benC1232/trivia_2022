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
private:
	sqlite3* _db;
	void createTables();
};
