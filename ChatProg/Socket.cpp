#include "stdafx.h"
#include "Socket.h"

#pragma region Socket
Socket::Socket()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		std::cerr << "Error With WSAStartup" << std::endl;
		system("pause");
		WSACleanup();
		exit(10);
	}

	//Make the socket
	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mySocket == INVALID_SOCKET)
	{
		std::cerr << "Error Creating Socket" << std::endl;
		system("pause");
		WSACleanup();
		exit(11);
	}

	myBackup = mySocket;
}


Socket::~Socket()
{
	WSACleanup();
}

bool Socket::SendData(const char* buffer)
{
	send(mySocket, buffer, strlen(buffer), 0);
	return true;
}

int Socket::RecvData(char *buffer, int size)
{
	int i = recv(mySocket, buffer, size, 0); 
	buffer += '\0';
	return i;
}
void Socket::CloseConnection()
{
	std::cout << "CLOSE CONNECTION" << std::endl;
	closesocket(mySocket);
	mySocket = myBackup;
}

void Socket::GetAndSendMessage()
{
	std::string message;
	std::cin.ignore();
	std::cout << "Send > ";
	std::cin >> message;
	SendData(message.c_str());
}

#pragma endregion Socket


#pragma region ClientSocket
void ClientSocket::ConnectToServer(const char* ipAddress, int port)
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = inet_addr(ipAddress);
	myAddress.sin_port = htons(port);

	std::cout << "Connecting\n";
	if (connect(mySocket, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR)
	{
		std::cerr << "Client failed to connect\n";
		system("pause");
		WSACleanup();
		exit(13);
	}
	std::cout << "Connected to server\n";
	while (1)
	{
		GetAndSendMessage();
	}
}
#pragma endregion ClientSocket


#pragma region ServerSocket
void ServerSocket::StartHosting(int port)
{
	Bind(port);
	Listen();
}

void ServerSocket::Bind(int port)
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
	myAddress.sin_port = htons(port);

	std::cout << "BIND TO PORT\n";

	if (bind(mySocket, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to connect\n";
		system("pause");
		WSACleanup();
		exit(14);
	}
}

void ServerSocket::Listen()
{
	std::cout << "LISTENING FOR CLIENT...\n";

	if (listen(mySocket, 1) == SOCKET_ERROR)
	{
		std::cerr << "Error Listening on Socket\n";
		system("pause");
		WSACleanup();
		exit(15);
	}

	std::cout << "ACCEPT CONNECTION...\n";

	acceptSocket = accept(myBackup, NULL, NULL);
	while (acceptSocket == SOCKET_ERROR)
	{
		acceptSocket = accept(myBackup, NULL, NULL);
	}
	mySocket = acceptSocket;
	std::cout << "Client Connected\n";
	char buf[256];
	while (1)
	{
		int len = this->RecvData(buf, 256);
		std::string msg(buf, len);
		std::cout << msg;
	}
}
#pragma endregion ServerSocket