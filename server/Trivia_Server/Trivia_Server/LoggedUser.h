#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string username);
	LoggedUser() = default;

	// < operator
	bool operator<(const LoggedUser& other) const;
	bool operator>(const LoggedUser& other) const;

	std::string getUsername();
private:
	std::string m_username;
};
