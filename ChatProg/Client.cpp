#include "stdafx.h"
#include "Client.h"


Client::Client()
{
	chatLog = std::vector<chat>();
}

Client::Client(std::string user)
{
	userName = user;
	chatLog = std::vector<chat>();
}

Client::~Client()
{
}

std::string Client::getUserName()
{
	return "";
}

Client::chat Client::getChatById(long id)
{
	return *new chat();
}

std::vector<Client::chat> Client::getChatLog()
{
	return *new std::vector<Client::chat>();
}