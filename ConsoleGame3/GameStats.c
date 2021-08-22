#include "Globals.h"
#include <stdio.h>

/*
	Try to connect to a server with the configuration settings.
	If there is no response from the server, ask if the user wants to be player1 and 

*/
int InitGame() {
	HWND hwnd = GetConsoleWindow();
	RECT r = { 200, 200, 1720, 880 };
	MoveWindow(
		hwnd,
		r.left,
		r.top,
		r.right,
		r.bottom,
		TRUE
		);

	STDO = GetStdHandle(STANDARDOUT);
	STDI = GetStdHandle(STANDARDIN);
	HWND_CONSOLE = GetConsoleWindow();
	GetConsoleScreenBufferInfo(STDO, &csbi_saved);

	//Hide the cursor so it doesn't flashy-flashy us!
	CONSOLE_CURSOR_INFO cci = { 1, FALSE };
	SetConsoleCursorInfo(STDO, &cci);

	IS_SERVER = FALSE;
	IS_CLIENT = FALSE;
	ConnectMsgOffset = 1;
	WSAMainMsg = WM_USER + ConnectMsgOffset; // Values below 0x400 are reserved

	return ALLGOOD;
}


int DisplayDebugInfo() {
	COORD c = { 0, csbi_saved.srWindow.Bottom-1  };
	SetConsoleCursorPosition( STDO, c);

	printf("Framerate: %d \tCurInputs value: %d                     ", FRAMERATE, curInputs);
	return ALLGOOD;
}