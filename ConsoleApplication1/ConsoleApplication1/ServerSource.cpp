#include "ServerSource.h"

//https://wwwi.tistory.com/69
//https://qerogram.tistory.com/entry/3-%EC%86%8C%EC%BC%93-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D%EC%9C%BC%EB%A1%9C-%EA%B0%84%EB%8B%A8%ED%95%9C-%EC%B1%84%ED%8C%85%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8-%EB%A7%8C%EB%93%A4%EA%B8%B02-in-C?category=697086
//https://kevinthegrey.tistory.com/26
//https://slaner.tistory.com/40?category=546117
//http://blog.naver.com/PostView.nhn?blogId=ym7596&logNo=220959084844&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView 
void ServerSource::StartServer()
{
	while (true)
	{
		char cRecBuffer[PACKET_SIZE] = {};
		char cSendBuffer[PACKET_SIZE] = "Send";

		recv(mClientSocket, cRecBuffer, PACKET_SIZE, 0);
		std::cout << "Rev : " << cRecBuffer << std::endl;
		if (strcmp(cRecBuffer, "q") == 0)
			return;

		send(mClientSocket, cSendBuffer, strlen(cSendBuffer), 0);
		std::cout << cSendBuffer << std::endl;
	}
}


