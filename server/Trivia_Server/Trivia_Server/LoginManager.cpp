#include "LoginManager.h"
/*
* constructor for LoginManager
* input: database
* output: none
*/
LoginManager::LoginManager(IDatabase* db)
{
	this->db = db;
}

LoginManager::~LoginManager()
{
}
/*
* function to check if the user is valid, if it is valid, it will return true and add the user to the vector
* input: username, password
* output: true if the user is valid, false if the user is not valid
*/
bool LoginManager::login(std::string username, std::string password)
{
	const LoggedUser user = LoggedUser(username);
	const bool isLogged = std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user) != this->m_loggedUsers
		.end();
	if (db->doesUserExist(username) && db->doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(user);
		return true;
	}
	return false;
}

/*
* function to put the user in the database and add the user to the vector if it doesnt exist yet
* input: username, password, email
* output: true if the user is valid, false if the user is not valid
*/
bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (db->doesUserExist(username))
	{
		return false;
	}
	db->addNewUser(username, password, email);
	const LoggedUser user = LoggedUser(username);
	this->m_loggedUsers.push_back(user);
	return true;
}
/*
* function to remove the user from the vector
* input: username
* output: true if the user was removed, false if the user was not removed
*/
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