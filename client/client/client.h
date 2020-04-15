#pragma once

#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <WinSock2.h>
#include <process.h>

#define PORT 333 
#define PACKET_SIZE 1024

using namespace std;

class ClientSource
{
private:
	SOCKET mClientSocket;
	bool mIsQuit = false;
	const char* mServerIP;

public:
	void StartClient();
	void RequestMsg(const char* msg);
	void QuitCLient();

	ClientSource(const char* server_ip)
	{
		mServerIP = server_ip;

		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);


		mClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		SOCKADDR_IN tAddr = {};
		tAddr.sin_family = AF_INET;
		tAddr.sin_port = htons(PORT);
		tAddr.sin_addr.s_addr = inet_addr(mServerIP);
		connect(mClientSocket, (SOCKADDR*)& tAddr, sizeof(tAddr));
	}

	~ClientSource()
	{
		closesocket(mClientSocket);
		WSACleanup();
	}

};