// ConsoleGame3.cpp : Defines the entry point for the application.
#pragma comment(lib, "Ws2_32.lib")

extern "C" { 
#include "BasicHi.h" 
#include "Globals.h"
#include "GameBoard.h"
#include "Player.h"
#include "input.h"
#include "GameStats.h"
#include "Comms.h"
}
#include "ConsoleGame3.h"
#define _WINSOCKAPI_
#include <Windows.h>

using namespace std;

int main(int argc, char** argv)
{
	if(argc >=3) printf("%s %s", argv[1], argv[2]);
	PlayerStats player1 = InitPlayer();
	PlayerStats player2 = InitPlayer();
	player2.playerIcon = '%';
	player2.pos.Y += 9;
	player2.pos.X += 9;


	InitGame();
	StartMenu();
	Connect();
	ClearBoard();


	//Main Game Loop. TODO: organize this in a subfile
	while(true) {
		CheckForConsoleInput();
		if (curInput == quit) break;
		DisplayPlayer(&player1);
		DisplayPlayer(&player2);
		DisplayDebugInfo();
		FRAMEWAIT;
	}
	


	//OK, laying out some actual psuedo code now:
	/*
	StartMenu() // Instead of trying for a specific server/client, both will try to talk to a server first. If there is no server, both will set up a server with 
					The given IP/ListenPort and then set up another attempt at talking to the given server address. The first to recieve a response will set a 
	InitPlayers()
	InitLevel(int)

	StartGame()
		UpdateGame() //Runs every 10ms Broadcast in Globals.h???
	
	
	
	
	
	*/







	return 0;
}
