#pragma once
#include "input.h"

#define ALLGOOD 0
#define OHNOES -1

#define STANDARDIN -10
#define STANDARDOUT -11
#define STANDARDERR -12
#define FRAMERATE 60
#define FRAMEWAIT Sleep(1000/FRAMERATE)

WORD boardBGColor;

//This state is updated by input.c:CheckForConsoleInput()
inputs curInput;
int curInputs;


// UI globals:
HANDLE STDO;
HANDLE STDI;
HWND HWND_CONSOLE;
CONSOLE_SCREEN_BUFFER_INFO csbi_saved;


// Comms globals:
BOOL IS_SERVER;
BOOL IS_CLIENT;
SOCKET serverSocket;
SOCKET clientSocket;
u_long WSAMainMsg;
u_int ConnectMsgOffset;






