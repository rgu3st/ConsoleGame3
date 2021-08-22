#include <WinSock2.h>
#include "Globals.h"
#include <stdio.h>



#define WSAVMINOR 2
#define WSAVMAJOR 2
#define DEFAULTIP "127.0.0.1"
#define DEFAULTPORT 5353

// Ref: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
int InitWSA() {
	WORD version = MAKEWORD(WSAVMAJOR, WSAVMINOR); // (lobyte, hibyte)
	WSADATA wsaData;
	int res;
	res = WSAStartup(version, &wsaData);
	if (res != 0) {
		printf("No WSA startup becuase of: %d\n", WSAGetLastError());
		return OHNOES;
	}
	if (LOBYTE(wsaData.wVersion) != WSAVMAJOR || HIBYTE(wsaData.wVersion) != WSAVMINOR) {
		printf("No WSA startup becuase of: %d\n", WSAGetLastError());
		WSACleanup();
		return OHNOES;
	}
	printf("WSA Init all good!\n");
	return ALLGOOD;
}

int DeinitWSA() {
	WSACleanup(); //MSDN says to call this when finished using the Winsock dll
	return ALLGOOD;
}


int DeinitServer() {

}

int InitServer() {
	InitWSA();
	SOCKADDR_IN serverSockAddr;
	int res; 
	char* greeting = "Welcome, Player 2!";

	// Set up socket for server
	serverSocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (serverSocket == INVALID_SOCKET) {
		printf("Crap no good server socket!\n");
		return OHNOES;
	}
	// Serversocket sockaddr_in data: 
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.s_addr = inet_addr(DEFAULTIP);
	serverSockAddr.sin_port = htons(DEFAULTPORT);
	// Actually bind!
	res = bind(serverSocket, (SOCKADDR*)&serverSockAddr, sizeof(serverSockAddr));
	if (res == SOCKET_ERROR) {
		printf("Couldn't bind because of error %d! I REALLY need a better debug print method...\n", WSAGetLastError());
	}
	printf("Yep, server setup all good!");
	return ALLGOOD;
}

int InitClient() {
	InitWSA();
	SOCKADDR_IN clientSockAddr;
	int res;
	char* greeting = "Player 1: let me in!";

	clientSockAddr.sin_family = AF_INET;
	clientSockAddr.sin_addr.s_addr = inet_addr(DEFAULTIP);
	clientSockAddr.sin_port = htons(DEFAULTPORT);

	clientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	res = connect(clientSocket, (SOCKADDR*)&clientSockAddr, sizeof(clientSockAddr));
	if (res == SOCKET_ERROR) {
		closesocket(clientSocket);
		printf("Unable to connect to server: %ld\n", WSAGetLastError());
		DeinitWSA();
		return OHNOES;
	}
	return ALLGOOD;
}

int Connect() {
	if (IS_SERVER) {
		InitServer();
		printf("Waiting for player 2...\n");
		WSAAsyncSelect(serverSocket, HWND_CONSOLE, WSAMainMsg, FD_READ | FD_WRITE);
	}
	else {
		InitClient();
	}

}