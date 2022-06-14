#include "LoggedUser.h"
/*
* constructor
* input: username
* output: none
*/
LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}
/*
* < operator overloading
* input: other LoggedUser
* output: true if this LoggedUser is less than other LoggedUser (lexicographically)
*/
bool LoggedUser::operator<(const LoggedUser& other) const
{
	return (this->m_username < other.m_username);
}
/*
* > operator overloading
* input: other LoggedUser
* output: true if this LoggedUser is greater than other LoggedUser (lexicographically)
*/
bool LoggedUser::operator>(const LoggedUser& other) const
{
	return (this->m_username > other.m_username);
}
/*
* == operator overloading
* input: other LoggedUser
* output: true if this LoggedUser is equal to other LoggedUser (lexicographically)
*/
bool LoggedUser::operator==(const LoggedUser& other) const
{
	return (this->m_username == other.m_username);
}
/*
* username getter
* input: none
* output: username
*/
std::string LoggedUser::getUsername()
{
	return this->m_username;
}