#pragma once
class Client
{
	typedef std::tuple<long, std::tm, std::string> chat;
private:
	std::string userName;
	std::vector<chat> chatLog;
public:
	Client();
	Client(std::string user);
	~Client();
	std::string getUserName();
	chat getChatById(long id);
	std::vector<chat> getChatLog();
};

