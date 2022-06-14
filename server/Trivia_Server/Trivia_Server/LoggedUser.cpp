#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

bool LoggedUser::operator<(const LoggedUser& other) const
{
	return (this->m_username < other.m_username);
}

bool LoggedUser::operator>(const LoggedUser& other) const
{
	return (this->m_username > other.m_username);
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return (this->m_username == other.m_username);
}

std::string LoggedUser::getUsername()
{
	return this->m_username;
}