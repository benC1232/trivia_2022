#include "Question.h"

std::string Question::getQuestion()
{
	return this->m_question;
}

std::string Question::getCorrectAnswer()
{
	return this->m_answers[0];
}

std::vector<std::string> Question::getIncorrectAnswers()
{
	return std::vector<std::string>(this->m_answers.begin() + 1, this->m_answers.end());
}