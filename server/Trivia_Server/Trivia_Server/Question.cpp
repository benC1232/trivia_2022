#include "Question.h"

std::string Question::getQuestion()
{
	return this->m_question;
}

std::string Question::getCorrectAnswer()
{
	return this->m_answers.at(0);
}

std::vector<std::string> Question::getIncorrectAnswers()
{
	return std::vector<std::string>(this->m_answers.begin() + 1, this->m_answers.end());
}

void Question::setQuestion(std::string question)
{
	this->m_question = question;
}

void Question::setCorrectAnswer(std::string correctAnswer)
{
	this->m_answers.push_back(correctAnswer);
}

void Question::setIncorrectAnswers(std::vector<std::string> incorrectAnswers)
{
	this->m_answers.insert(this->m_answers.begin() + 1, incorrectAnswers.begin(), incorrectAnswers.end());
}