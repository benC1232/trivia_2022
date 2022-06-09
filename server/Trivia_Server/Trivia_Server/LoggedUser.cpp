#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

bool LoggedUser::operator<(const LoggedUser& other) const
{
	return  (this->m_username.length() < other.m_username.length());
}

bool LoggedUser::operator>(const LoggedUser& other)const
{

	return  (this->m_username.length() > other.m_username.length());
}

std::string LoggedUser::getUsername()
{
	return this->m_username;
}