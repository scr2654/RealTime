#pragma once
#pragma comment(lib, "ws2_32")

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

#define PORT 333 
#define PACKET_SIZE 1024

using namespace std;

class ServerSource
{
	private :
		SOCKET mServerSocket;
		SOCKET mClientSocket;


	public:
		void StartServer();


	ServerSource()
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		mServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		SOCKADDR_IN tListenAddr = {};
		tListenAddr.sin_family = PF_INET;
		tListenAddr.sin_port = htons(PORT);
		tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		bind(mServerSocket, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));
		listen(mServerSocket, SOMAXCONN);

		SOCKADDR_IN tClntAddr = {};
		int iClntSize = sizeof(tClntAddr);
		mClientSocket = accept(mServerSocket, (SOCKADDR*)& tClntAddr, &iClntSize);
	}

	~ServerSource()
	{
		closesocket(mServerSocket);
		closesocket(mClientSocket);
		WSACleanup();
	}

};

