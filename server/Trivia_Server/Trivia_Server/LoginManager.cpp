#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db)
{
	this->db = db;
}

LoginManager::~LoginManager()
{
}

bool LoginManager::login(std::string username, std::string password)
{
	bool isExist = db->doesUserExist(username);
	bool passwordMatch = db->doesPasswordMatch(username, password);
	if (db->doesUserExist(username) && db->doesPasswordMatch(username, password))
	{
		LoggedUser user = LoggedUser(username);
		this->m_loggedUsers.push_back(user);
		return true;
	}
	else
	{
		return false;
	}
}

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (db->doesUserExist(username))
	{
		return false;
	}
	else
	{
		db->addNewUser(username, password, email);
		LoggedUser user = LoggedUser(username);
		this->m_loggedUsers.push_back(user);
		return true;
	}
}

bool LoginManager::logout(std::string username)
{
	for (int i = 0; i < m_loggedUsers.size(); i++)
	{
		if (m_loggedUsers[i].getUsername() == username)
		{
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
			return true;
		}
	}
	return false;
}