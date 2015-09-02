// ChatProg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Socket.h"

int main(int argc, char** argv)
{
	std::string arg1 = "cCsS";
	std::string arg2 = "0123456789";
	if (argc != 3)
	{
		std::cout << "WRONG ARGUMENTS: PROPER FORMAT IS this.exe -[cs] -{0-65535}";
		return 0;
	}
	std::string role = argv[1];
	role = role[0]=='-'?role.substr(1):role;
	std::string portstr = argv[2];
	portstr = portstr[0] == '-'?portstr.substr(1):portstr;

	int port = std::stoi(portstr);

	if (role.length() != 1 || arg1.find(role) == std::string::npos)
	{
		std::cout << "WRONG ARGUMENTS: PROPER FORMAT IS this.exe -[cs] -[0-9]{5}";
		return 0;
	}
	if (port < 0 || port > 65535)
	{
		std::cout << "WRONG ARGUMENTS: PROPER FORMAT IS this.exe -[cs] -[0-9]{5}";
		return 0;
	}

	if (role == "c" || role == "C")
	{
		ClientSocket* me = new ClientSocket();
		me->ConnectToServer("127.0.0.1", port);
	}

	if (role == "s" || role == "S")
	{
		ServerSocket* me = new ServerSocket();
		me->StartHosting(port);

	}
	return 0;
}

