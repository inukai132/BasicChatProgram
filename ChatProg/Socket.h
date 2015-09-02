#pragma once
class Socket
{
public:
	Socket();
	~Socket();
	bool SendData(const char*);
	int RecvData(char*, int);
	void CloseConnection();
	void GetAndSendMessage();
protected:
	WSADATA wsaData;
	SOCKET mySocket;
	SOCKET myBackup;
	SOCKET acceptSocket;
	sockaddr_in myAddress;
};

class ServerSocket : public Socket
{
public:
	void Listen();
	void Bind(int port);
	void StartHosting(int port);
};

class ClientSocket : public Socket
{
public:
	void ConnectToServer(const char* ipAddress, int port);
};