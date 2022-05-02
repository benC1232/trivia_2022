#pragma once
#include <string>
#include "sqlite3.h"
#include <io.h>
#include <iostream>
class IDatabase
{
public:
	IDatabase();
	~IDatabase();
	bool doesUserExist(std::string username);
	bool doesPasswordMatch(std::string username, std::string password);
	void addNewUser(std::string username, std::string password, std::string email);
private:
	sqlite3* _db;
	void createTables();
};