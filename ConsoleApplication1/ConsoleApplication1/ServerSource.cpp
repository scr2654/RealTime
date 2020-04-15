#include "ServerSource.h"

//https://wwwi.tistory.com/69



void ServerSource::StartServer()
{
	while (true)
	{
		char cRecBuffer[PACKET_SIZE] = {};
		char cSendBuffer[PACKET_SIZE] = {};

		recv(mClientSocket, cRecBuffer, PACKET_SIZE, 0);
		std::cout << cRecBuffer << std::endl;
		send(mClientSocket, cSendBuffer, strlen(cSendBuffer), 0);
		std::cout << cSendBuffer << std::endl;
	}
}


