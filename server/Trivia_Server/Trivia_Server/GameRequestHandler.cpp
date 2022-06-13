#include "GameRequestHandler.h"
#define LEAVE_GAME_CODE 14
#define GET_QUESTION_CODE 15
#define SUBMIT_ANSWER_CODE 16
#define GET_GAME_RESULT_CODE 17

/*
 * the constructor of the gameRequestHandler class
 * input: gameManager(GameManager*), loggedUser(LoggedUser), requestHandlerFactory(RequestHandlerFactory*), game(Game*)
 */
GameRequestHandler::GameRequestHandler(GameManager* gameManager, LoggedUser loggedUser, RequestHandlerFactory* requestHandlerFactory, Game* game)
{
	this->m_gameManager = gameManager;
	this->m_loggedUser = loggedUser;
	this->m_requestHandlerFactory = requestHandlerFactory;
	this->m_game = game;
	this->questionCount = 0;
	this->isFirstRequest = true;
}

GameRequestHandler::~GameRequestHandler()
{
	delete this->m_gameManager;
	delete this->m_requestHandlerFactory;
	delete this->m_game;
}

/*
 * a function that finds if a request is relevant to the game
 * input: requestInfo(RequestInfo)
 * output: true if the request is relevant, false otherwise
 */
bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == LEAVE_GAME_CODE || requestInfo.id == GET_QUESTION_CODE || requestInfo.id == SUBMIT_ANSWER_CODE || requestInfo.id == GET_GAME_RESULT_CODE;
}

/*
 * a function that handles all of the requests that are relevant to the game
 * input: requestInfo(RequestInfo)
 * output: RequestResult
 */
RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == LEAVE_GAME_CODE)
	{
		result = leaveGame();
	}
	else if (requestInfo.id == GET_QUESTION_CODE)
	{
		result = getQuestion();
	}
	else if (requestInfo.id == SUBMIT_ANSWER_CODE)
	{
		result = submitAnswer(requestInfo);
	}
	else if (requestInfo.id == GET_GAME_RESULT_CODE)
	{
		result = getGameResults();
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [room admin request handler has received a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

/*
 * a function that handles the get question request
 * output: RequestResult
 */
RequestResult GameRequestHandler::getQuestion()
{
	GetQuestionResponse response;
	RequestResult result;
	try
	{
		Question returnedQuestion = this->m_requestHandlerFactory->getGameManager().getGame(this->m_loggedUser)->getQuestionForUser(this->m_loggedUser);
		response.question = returnedQuestion.getQuestion();
		std::vector<std::string> answers;
		answers = returnedQuestion.getIncorrectAnswers();
		answers.push_back(returnedQuestion.getCorrectAnswer());
		response.answers = answers;
		response.status = 1;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		response.question = "";
		std::vector<std::string> answers;
		answers.push_back("");
		answers.push_back("");
		answers.push_back("");
		answers.push_back("");
		response.answers = answers;
		response.status = 0;
	}
	result.buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(response);
	result.newHandler = this;
	return result;
}


/*
 * a function that handles the submit answer request
 * output: RequestResult
 */
RequestResult GameRequestHandler::submitAnswer(const RequestInfo requestInfo)
{
	RequestResult result;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
	SubmitAnswerResponse response;
	response.status = SUBMIT_ANSWER_CODE;
	response.isCorrect = this->m_game->submitAnswer(this->m_loggedUser, request.answer, request.responseTime);
	result.buffer = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(response);
	result.newHandler = this;
	return result;
}

/*
 * a function that handles the get game results request
 * output: RequestResult
 */
RequestResult GameRequestHandler::getGameResults()
{
	RequestResult result;
	GetGameResultsResponse response;
	response.status = GET_GAME_RESULT_CODE;
	response.results = this->m_game->getResults();
	int index = 0;
	if (this->isFirstRequest)
	{
		this->isFirstRequest = false;
		for (int i = 0; i < response.results.size(); i++)
		{
			if (response.results[i].username == this->m_loggedUser.getUsername())
			{
				index = i;
				break;
			}
		}
		this->m_requestHandlerFactory->getDatabase().addStatistics(response.results[index].username, response.results[index].averageAnswerTime, response.results[index].correctAnswerCount, response.results[index].wrongAnswerCount);
	}
	result.buffer = JsonResponsePacketSerializer::serializeGetGameResultResponse(response);
	result.newHandler = this;
	return result;
}

/*
 * a function that handles the leave game request
 * output: RequestResult
 */
RequestResult GameRequestHandler::leaveGame() const
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
