#include "Question.h"

//returns the question
std::string Question::getQuestion()
{
	return this->m_question;
}

//returns the answer
std::string Question::getCorrectAnswer()
{
	return this->m_answers.at(0);
}

//returns the incorrect answers
std::vector<std::string> Question::getIncorrectAnswers()
{
	return std::vector<std::string>(this->m_answers.begin() + 1, this->m_answers.end());
}

//set the question
void Question::setQuestion(std::string question)
{
	this->m_question = question;
}


//set the correct answers
void Question::setCorrectAnswer(std::string correctAnswer)
{
	this->m_answers.push_back(correctAnswer);
}


//set the incorrect answers
void Question::setIncorrectAnswers(std::vector<std::string> incorrectAnswers)
{
	this->m_answers.insert(this->m_answers.begin() + 1, incorrectAnswers.begin(), incorrectAnswers.end());
}