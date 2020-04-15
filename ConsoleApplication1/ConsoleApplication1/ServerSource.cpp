#include "ServerSource.h"

// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#pragma comment(lib, "ws2_32")

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#define PORT 333 
#define PACKET_SIZE 1024
unsigned WINAPI sendMsg(void* arg);
SOCKET hClient;
//https://wwwi.tistory.com/69

using namespace std;

unsigned WINAPI recMsg(void* arg)
{
	while (1)
	{
		char cBuffer[PACKET_SIZE] = {};
		recv(hClient, cBuffer, PACKET_SIZE, 0);
		printf("Msg : %s\n", cBuffer);
	}
}


void Chatting()
{
	HANDLE sendThread, recThread;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	hListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);


	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);

	recThread = (HANDLE)_beginthreadex(NULL, 0, recMsg, NULL, 0, NULL);

	while (true)
	{
		sendMsg(NULL);
	}
	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();
}

int main()
{
	//Chatting();

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = PF_INET;
	tListenAddr.sin_port = htons(333);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);


	char cMsg[2048] = {};
	strcpy_s(cMsg, "HTTP/1.0 200 OK\r\ ""www.naver.com""");
	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);

	while (true)
	{
		char cBuffer[PACKET_SIZE] = {};
		recv(hClient, cBuffer, PACKET_SIZE, 0);
		std::cout << cBuffer << std::endl;
		send(hClient, cMsg, strlen(cMsg), 0);
		std::cout << cMsg << std::endl;
	}

	closesocket(hListen);
	closesocket(hClient);
	WSACleanup();

	return 0;
}

unsigned WINAPI sendMsg(void* arg)
{

	char aa[PACKET_SIZE];
	std::cout << "input : ";
	std::cin >> aa;

	//cMsg = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n초간단 HTTP 서버\\n";

	send(hClient, aa, strlen(aa), 0);

	return 0;
}


