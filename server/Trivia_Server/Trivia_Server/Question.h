#pragma once
#include <string>
#include <vector>
//this class is in the uml of V4.0.0 but is required in the IDatabase interface in V2.0.0
class Question
{
public:
	Question() = default;
	std::string getQuestion();
	std::string getCorrectAnswer();
	std::vector<std::string> getIncorrectAnswers();
private:
	std::string m_question;
	std::vector<std::string> m_answers;
};
