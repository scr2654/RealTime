#include "client.h"

void ClientSource::StartClient()
{
	while (true)
	{
		char cRecBuffer[PACKET_SIZE] = {};
		recv(mClientSocket, cRecBuffer, PACKET_SIZE, 0);
		std::cout << cRecBuffer << std::endl;

		if (mIsQuit)
			return;
	}

}

void ClientSource::RequestMsg(const char* msg)
{
	send(mClientSocket, msg, strlen(msg), 0);
	if (strcmp(msg, "q") == 0)
		QuitCLient();
}

void ClientSource::QuitCLient()
{
	mIsQuit = true;
}

#include "client.h"
#include <process.h>
#include <iostream>

using namespace std;

unsigned WINAPI ThreadFunction1(void* arg) {
	ClientSource mainServer = *((ClientSource*)arg);
	mainServer.StartClient();

	return 0;
}


unsigned WINAPI ThreadFunction2(void* arg) {
	ClientSource mainServer = *((ClientSource*)arg);

	while (true)
	{
		char msg[1024];
		cin >> msg;
		mainServer.RequestMsg(msg);
	}
	return 0;
}

/*
void main()
{
	const char* ip = "220.79.202.110";
	ClientSource mainServer = ClientSource(ip);

	HANDLE sendThread, recThread;

	recThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction1, (void*)& mainServer, 0, NULL);
	//sendThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction2, (void*)& mainServer, 0, NULL);

	while (true)
	{
	}
}
*/

