#pragma once
#include <vector>
#include "SqliteDataBase.h"
#include "LoggedUser.h"
class LoginManager
{
public:
	LoginManager() = default;
	LoginManager(IDatabase* db);
	~LoginManager();
	bool login(std::string username, std::string password);
	bool signup(std::string username, std::string password, std::string email);
	bool logout(std::string username);
private:
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* db;
};
