#pragma once
#include <vector>
#include "SqliteDataBase.h"
#include "LoggedUser.h"
class LoginManager
{
public:
	LoginManager();
	~LoginManager();
	bool login(std::string username, std::string password);
	bool signup(std::string username, std::string password, std::string email);
	bool logout(std::string username);
private:
	std::vector<LoggedUser> m_loggedUsers;
	SqliteDataBase m_db;
};
