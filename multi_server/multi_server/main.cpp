// sockserver.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
//#include <stdafx.h>
#include <winsock2.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib" )

struct sockets {
	SOCKET s1;
	SOCKET s2;
};


unsigned int __stdcall Sending(void* data)
{
	
	sockets* sok = (sockets*)data;
	sockets Sok = *sok;

	//SOCKET* client = (SOCKET*)data;
	SOCKET Client = Sok.s1;
	//SOCKET* client2 = (SOCKET*)data;
	//SOCKET Client2 = *client2;
	SOCKET Client2 = Sok.s2;

	char send1[100];
	char send2[100];
	sprintf(send1, "white");
	sprintf(send2, "black");

	send(Client, send1, sizeof(send1), 0);
	send(Client2, send2, sizeof(send2), 0);

	char recv1[200];
	char recv2[200];

	while (true) {

		if (recv(Client, recv1, 200, 0) == -1) {
			std::cout << "brak polaczenia 1" << std::endl;
			std::string str = "win";
			char send_me[5];
			strcpy(send_me, str.c_str());
			send(Client2, send_me, sizeof(send_me), 0);
			closesocket(Client);
			closesocket(Client2);
			break;
		}
		//recv(Client, recv1, 200, 0);
		std::cout << "RUCHHHH" << std::endl;
		std::cout << recv1 << "T: " << GetCurrentThreadId() << std::endl;
		sprintf(send2, recv1);

		std::cout << Client2 << std::endl;

		
		send(Client2, send2, sizeof(send2), 0);
		
		if (recv(Client2, recv2, 200, 0) == -1) {
			std::cout << "brak polaczenia 2" << std::endl;
			std::string str = "win";
			char send_me[5];
			strcpy(send_me, str.c_str());
			send(Client, send_me, sizeof(send_me), 0);
			closesocket(Client);
			closesocket(Client2);
			break;
		}

		std::cout << "RUCHHHH" << std::endl;
		std::cout << recv2 << "T: " << GetCurrentThreadId() << std::endl;
		sprintf(send1, recv2);

		send(Client, send1, sizeof(send1), 0);

		ZeroMemory(recv1, 200);
		ZeroMemory(recv2, 200);
		ZeroMemory(send1, 100);
		ZeroMemory(send2, 100);
		std::cout << "ZEROWANKO" << std::endl;
		std::cout << recv1 << std::endl;
		std::cout << recv2 << std::endl;
		std::cout << send1 << std::endl;
		std::cout << send2 << std::endl;
	}
	return 0;
}


int main()
{
	int players_number = 0;
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client, client_buf;
	sockets socks;


	addr.sin_family = AF_INET;
	addr.sin_port = htons(2222);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");// warmomg depracated inet_addr("127.0.0.1");  INADDR_ANY

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 


	if (iResult)
	{
		printf("WSA startup failed");
		return 0;
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		printf("Invalid socket");
		return 0;
	}

	iResult = bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in));

	if (iResult)
	{

		printf("bind failed %u", GetLastError());

		return 0;
	}

	iResult = listen(sock, SOMAXCONN);

	if (iResult)
	{

		printf("iResult failed %u", GetLastError());

		return 0;
	}

	while (client = accept(sock, 0, 0))
	{
		if (client == INVALID_SOCKET)
		{
			printf("invalid client socket", GetLastError());
			continue;
		}

		if (players_number == 1) {
			socks.s2 = client;
			_beginthreadex(0, 0, Sending, (void*)&socks, 0, 0);
		}
		else {
			socks.s1 = client;
		}

		players_number = (players_number + 1) % 2;


		
		//_beginthreadex(0, 0, Sending, (void*)&client, 0, 0);


	}


	return 0;
}

