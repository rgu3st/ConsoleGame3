#include "Windows.h"
#include "Player.h"
#include "Globals.h"

playerStats InitPlayer() {
	playerStats ps = { {10,0}, 100, '@', FOREGROUND_RED, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED }; //Should we just use the board BG by default?? 
	return ps;
}



int UpdatePlayerPos(playerStats* ps) {
	//up, down, left, right
	if (curInputs & up ) {
		if (ps->pos.Y > csbi_saved.srWindow.Top) ps->pos.Y--;
	}
	if (curInputs & down ) {
		if (ps->pos.Y < csbi_saved.srWindow.Bottom) ps->pos.Y++;
	}
	if (curInputs & left ) {
		if (ps->pos.X > csbi_saved.srWindow.Left) ps->pos.X--;
	}
	if (curInputs & right ) {
		if (ps->pos.X < csbi_saved.srWindow.Right) ps->pos.X++;
	}
	return ALLGOOD;
}


int DisplayPlayer(playerStats* ps) {
	//set colors/position
	
	GetConsoleScreenBufferInfo(STDO, &csbi_saved);
	SetConsoleCursorPosition(STDO, ps->pos);
	SetConsoleTextAttribute(STDO, ps->foregroundColor | boardBGColor);
	//print
	//printf("%c", ps.playerIcon);
	char towrite[2] = { ' ', '\0' };
	WriteConsole(STDO, towrite, 1, NULL, NULL);
	UpdatePlayerPos(ps);
	SetConsoleCursorPosition(STDO, ps->pos);
	towrite[0] = ps->playerIcon;
	WriteConsole(STDO, towrite, 1, NULL, NULL);
	//reset colors/position
	SetConsoleTextAttribute(STDO, csbi_saved.wAttributes);
	return ALLGOOD;
}