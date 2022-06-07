#include "GameRequestHandler.h"
#define LEAVE_GAME_CODE 14
#define GET_QUESTION_CODE 15
#define SUBMIT_ANSWER_CODE 16
#define GET_GAME_RESULT_CODE 17
GameRequestHandler::GameRequestHandler(GameManager* gameManager, LoggedUser loggedUser, RequestHandlerFactory* requestHandlerFactory, Game* game)
{
	this->m_gameManager = gameManager;
	this->m_loggedUser = loggedUser;
	this->m_requestHandlerFactory = requestHandlerFactory;
	this->m_game = game;
	this->questionCount = 0;
}

GameRequestHandler::~GameRequestHandler()
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == LEAVE_GAME_CODE || requestInfo.id == GET_QUESTION_CODE || requestInfo.id == SUBMIT_ANSWER_CODE || requestInfo.id == GET_GAME_RESULT_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == LEAVE_GAME_CODE)
	{
		result = leaveGame(requestInfo);
	}
	else if (requestInfo.id == GET_QUESTION_CODE)
	{
		result = getQuestion(requestInfo);
	}
	else if (requestInfo.id == SUBMIT_ANSWER_CODE)
	{
		result = submitAnswer(requestInfo);
	}
	else if (requestInfo.id == GET_GAME_RESULT_CODE)
	{
		result = getGameResults(requestInfo);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [room admin request handler has recived a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
	RequestResult result;
	Question returnedQuestion = this->m_game->getQuestionForUser(this->m_loggedUser);
	GetQuestionResponse response;
	response.question = returnedQuestion.getQuestion();
	std::vector<std::string> answers;
	answers = returnedQuestion.getIncorrectAnswers();
	answers.push_back(returnedQuestion.getCorrectAnswer());
	response.answers = answers;
	result.buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(response);
	result.newHandler = this;
	return result;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	RequestResult result;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
	SubmitAnswerResponse response;
	response.status = SUBMIT_ANSWER_CODE;
	response.isCorrect = this->m_game->submitAnswer(this->m_loggedUser, request.answer, request.responseTime);
	result.buffer = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(response);
	return result;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
	RequestResult result;
	GetGameResultsResponse response;
	response.status = GET_GAME_RESULT_CODE;
	response.results = this->m_game->getResults();
	result.buffer = JsonResponsePacketSerializer::serializeGetGameResultResponse(response);
	result.newHandler = this;
	return result;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
	RequestResult result;
	if (this->m_game->getNumOfPlayers() == 1)
	{
		this->m_gameManager->deleteGame(this->m_game);
	}
	else
	{
		this->m_game->removePlayer(this->m_loggedUser);
	}
	LeaveGameResponse response;
	response.status = LEAVE_GAME_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeLeaveGameResponse(response);
	result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(this->m_loggedUser);
	return result;
}