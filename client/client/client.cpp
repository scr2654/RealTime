// client.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

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
#define SERVER_IP "220.79.202.110"
SOCKET hSocket;

using namespace std;

unsigned int __stdcall sendMsg(void* arg)
{
	SOCKET sock = *((SOCKET*)arg);
	while (true)
	{
		char aa[PACKET_SIZE];
		std::cout << "input : ";
		std::cin >> aa;

		send(sock, aa, strlen(aa), 0);

	}
	return 0;
}

unsigned int __stdcall recMsg(void* arg)
{
	SOCKET sock = *((SOCKET*)arg);
	while (true)
	{

		char cBuffer[PACKET_SIZE] = {};
		recv(sock, cBuffer, PACKET_SIZE, 0);
		printf("Msg : %s\n", cBuffer);

	}
	return 0;
}
unsigned int __stdcall tempMsg(void* arg)
{
	while (true)
	{
		Sleep(30);
		cout << "Out" << endl;
	}
	return 0;
}


using namespace std;

void Client()
{
	HANDLE sendThread, recThread;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	connect(hSocket, (SOCKADDR*)& tAddr, sizeof(tAddr));
	
	recThread = (HANDLE)_beginthreadex(NULL, 0, recMsg, (void*)& hSocket, 0, NULL);
	
	while (true)
	{
		sendMsg((void*)& hSocket);
	}

	closesocket(hSocket);
	WSACleanup();
}

void http()
{
	

}


void main()
{
	Client();

	//Http();
	return;
}




