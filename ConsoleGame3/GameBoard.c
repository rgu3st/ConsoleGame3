#include "GameBoard.h"
#include "Globals.h"
#include <windows.h>
#include <stdio.h>


int SayHi() {
	printf("Hi from the Game Board.");
	return 0;
}

int ClearBoard() {
	//boardBGColor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	boardBGColor = 0; //For black :(
	COORD c = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi_saved;
	GetConsoleScreenBufferInfo(STDO, &csbi_saved);
	SetConsoleCursorPosition(STDO, c);
	SetConsoleTextAttribute(STDO, boardBGColor);

	

	DWORD written = 0;
	PCWSTR virtualSequence = L"\x1b[2J";
	if (!WriteConsoleW(STDO, virtualSequence, (DWORD)wcslen(virtualSequence), written, NULL)) {
		return OHNOES;
	}
	


	SetConsoleTextAttribute(STDO, csbi_saved.wAttributes);
	return ALLGOOD;
}

int UpdateBoard() {

	return ALLGOOD;
}



int StartMenu() {
	printf("\nREadY pLayER (1) or PlaYer (2)? > ");
	char response = getchar();
	if (response == '1') {
		printf("Starting server...");
		IS_SERVER = TRUE;
	}
	else if (response == '2') {
		printf("Connecting to server...");
		IS_CLIENT = TRUE;
	}
	else {
		printf(" Bad InpuT!");
		return OHNOES;
	}
	
	return ALLGOOD;
}
