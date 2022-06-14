#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser loggedUser, RoomManager* roomManager,
	StatisticsManager* statisticsManager,
	RequestHandlerFactory* requestHandlerFactory) : m_user(loggedUser),
	m_roomManager(m_roomManager), m_statisticsManager(statisticsManager), m_requestHandlerFactory(requestHandlerFactory)
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == CREATE_ROOM_REQUEST ||
		requestInfo.id == GET_ROOMS_REQUEST ||
		requestInfo.id == GET_PLAYERS_IN_ROOM_REQUEST ||
		requestInfo.id == JOIN_ROOM_REQUEST ||
		requestInfo.id == GET_STATISTICS_REQUEST ||
		requestInfo.id == LOGOUT_REQUEST ||
		requestInfo.id == HIGH_SCORE_GET ||
		requestInfo.id == ADD_QUESTION_CODE;
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo)
{
	RequestResult result;
	LogoutResponse num;
	LoginManager* manager = this->m_requestHandlerFactory->getLoginManager();
	manager->logout(this->m_user.getUsername());

	num.status = LOGOUT_REQUEST;
	result.newHandler = nullptr;
	result.buffer = JsonResponsePacketSerializer::serializeLogoutResponse(num);
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo) const
{
	RequestResult result;
	GetRoomResponse num;
	num.status = GET_ROOMS_REQUEST;
	const auto rooms = this->m_requestHandlerFactory->getRoomManager().getRooms();
	std::vector<RoomData> dataVector;
	for (auto room : rooms)
	{
		dataVector.push_back(room.getData());
	}
	num.rooms = dataVector;
	result.newHandler = m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	result.buffer = JsonResponsePacketSerializer::serializeGetRoomResponse(num);
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) const
{
	RequestResult result;
	GetPlayersInRoomsResponse num;
	const GetPlayersInRoomRequest getPlayersInRoomsRequest =
		JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);
	const auto rooms = this->m_roomManager->getRooms();
	for (auto room : rooms)
	{
		if (getPlayersInRoomsRequest.roomId == room.getData().id) num.players = room.getAllUsers();
	}
	result.buffer = JsonResponsePacketSerializer::serializeGetPlayersInRoomsResponse(num);
	result.newHandler = m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult MenuRequestHandler::getPersonStats(RequestInfo requestInfo)
{
	RequestResult result;
	GetPersonalStatsResponse num;
	num.status = GET_STATISTICS_REQUEST;
	num.statistics = this->m_statisticsManager->getUserStatistics(m_user.getUsername());
	result.buffer = JsonResponsePacketSerializer::serializeGetStatisticsResponse(num);
	result.newHandler = m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo requestInfo) const
{
	RequestResult result;
	GetHighScoreRespnse num;
	num.status = HIGH_SCORE_GET;
	num.statistics = this->m_statisticsManager->getHighScore();
	std::sort(num.statistics.begin(), num.statistics.end(), [](const std::string& a, const std::string& b) {
		std::size_t found = a.find(": ");
		int aScore = std::stoi(a.substr(found + 2));
		found = b.find(": ");
		int bScore = std::stoi(b.substr(found + 2));
		return aScore > bScore;
		});
	result.buffer = JsonResponsePacketSerializer::serializeGetHighScoreResponse(num);
	result.newHandler = m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo) const
{
	RequestResult result;
	JoinRoomResponse num;
	num.status = JOIN_ROOM_REQUEST;
	const JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(
		requestInfo.buffer);
	if (this->m_requestHandlerFactory->getRoomManager().getRoom(joinRoomRequest.roomId)->getData().maxPlayers == this->
		m_requestHandlerFactory->getRoomManager().getRoom(joinRoomRequest.roomId)->getAllUsersVector().size())
	{
		throw std::exception("Room is full");
	}
	this->m_requestHandlerFactory->getRoomManager().getRoom(joinRoomRequest.roomId)->addUser(this->m_user);
	result.buffer = JsonResponsePacketSerializer::serializeJoinRoomResponse(num);
	result.newHandler = this->m_requestHandlerFactory->createRoomMemberRequestHandler(
		this->m_user, this->m_requestHandlerFactory->getRoomManager().getRoom(joinRoomRequest.roomId));
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo) const
{
	RequestResult result;
	CreateRoomResponse num;
	num.status = CREATE_ROOM_REQUEST;
	const CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(
		requestInfo.buffer);
	RoomData roomData;
	roomData.timePerQuestion = createRoomRequest.answerTimeout;
	roomData.maxPlayers = createRoomRequest.maxUsers;
	roomData.name = createRoomRequest.roomName;
	roomData.numOfQuestionsInGame = createRoomRequest.questionCount;
	roomData.isActive = false;
	roomData.id = 0;
	const int id = this->m_requestHandlerFactory->getRoomManager().createRoom(m_user, roomData);
	result.buffer = JsonResponsePacketSerializer::serializeCreateRoomResponse(num);
	result.newHandler = this->m_requestHandlerFactory->createRoomAdminRequestHandler(
		this->m_user, this->m_requestHandlerFactory->getRoomManager().getRoom(id));
	return result;
}

RequestResult MenuRequestHandler::addQuestion(RequestInfo requestInfo)
{
	RequestResult result;
	AddQuestionResponse num;
	num.status = ADD_QUESTION_CODE;
	AddQuestionRequest addQuestionRequest = JsonRequestPacketDeserializer::deserializeAddQuestionRequest(
		requestInfo.buffer);
	Question question;
	question.setQuestion(addQuestionRequest.question);
	question.setCorrectAnswer(addQuestionRequest.correctAnswer);
	std::vector<std::string> wrongAnswers;
	wrongAnswers.push_back(addQuestionRequest.wrongAnswer1);
	wrongAnswers.push_back(addQuestionRequest.wrongAnswer2);
	wrongAnswers.push_back(addQuestionRequest.wrongAnswer3);
	question.setIncorrectAnswers(wrongAnswers);
	this->m_requestHandlerFactory->getDatabase().addQuestion(question);
	result.buffer = JsonResponsePacketSerializer::serializeAddQuestionResponse(num);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == LOGOUT_REQUEST)
	{
		result = signout(requestInfo);
	}
	else if (requestInfo.id == GET_ROOMS_REQUEST)
	{
		result = getRooms(requestInfo);
	}
	else if (requestInfo.id == GET_PLAYERS_IN_ROOM_REQUEST)
	{
		result = getPlayersInRoom(requestInfo);
	}
	else if (requestInfo.id == GET_STATISTICS_REQUEST)
	{
		result = getPersonStats(requestInfo);
	}
	else if (requestInfo.id == HIGH_SCORE_GET)
	{
		result = getHighScore(requestInfo);
	}
	else if (requestInfo.id == JOIN_ROOM_REQUEST)
	{
		try
		{
			result = joinRoom(requestInfo);
		}
		catch (std::exception e)
		{
			ErrorResponse num;
			num.message = "room is full";
			result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
			result.newHandler = this;
		}
	}
	else if (requestInfo.id == CREATE_ROOM_REQUEST)
	{
		result = createRoom(requestInfo);
	}
	else if (requestInfo.id == ADD_QUESTION_CODE)
	{
		result = addQuestion(requestInfo);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [login request handler has recived a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}