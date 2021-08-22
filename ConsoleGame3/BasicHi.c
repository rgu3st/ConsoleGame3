/*
* Help from:
* https://docs.microsoft.com/en-us/windows/console/getstdhandle
* 
*/

#include <stdio.h>
#include <string.h>
#include "Globals.h"
#include "Windows.h"

void DrawSquare(COORD top_left, size_t width, char forechar, HANDLE console) {
	COORD position = { 0, 0 };
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			position.X = top_left.X + i;
			position.Y = top_left.Y + j;
			SetConsoleCursorPosition(console, position);
			printf("%c", forechar);
		}
	}
	
}

int Hi() {
	//Get Handle to Standard Out:
	HANDLE stdh = GetStdHandle(STANDARDOUT);
	COORD c = { 0, 0 };
	//Save console attributes to return once I'm done:
	CONSOLE_SCREEN_BUFFER_INFO csbi_saved;
	GetConsoleScreenBufferInfo(stdh, &csbi_saved);
	//Some string to test new colors:
	char* diag = { "Hi! Diagonally" };

	for (int i = 0; i < strlen(diag); i++) {
		SetConsoleCursorPosition(stdh, c);
		SetConsoleTextAttribute(stdh, /*BACKGROUND_BLUE | BACKGROUND_GREEN |*/ BACKGROUND_RED );
		printf("%c", diag[i]);
		c.X++;
		c.Y++;
	}

	COORD sqc = { 4,4 };
	SetConsoleTextAttribute(stdh, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE);
	DrawSquare(sqc, 5, '@', stdh);
	
	SetConsoleTextAttribute(stdh, csbi_saved.wAttributes);
	return ALLGOOD;
}