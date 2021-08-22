#pragma once
#include <Windows.h>

typedef enum { up=1, down=2, left=4, right=8, shoot=16, pause=32, quit=64, none=0 }inputs;
int CheckForConsoleInput();
WORD GetInputKeyCode();
