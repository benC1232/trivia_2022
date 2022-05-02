#pragma once
#include <string>
#include "sqlite3.h"
#include <io.h>
#include <iostream>
class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
private:
	virtual void createTables() = 0;
};