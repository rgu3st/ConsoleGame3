#include <Windows.h>
#include <stdio.h>
#include "Globals.h"
#include "input.h"



/* Just trying ReadConsole now...*/
/*
int CheckForConsoleInput() {
    HANDLE stdi = GetStdHandle(STANDARDIN);
    LPVOID inputBuf[128];
    DWORD numCharsRead;
    if (!ReadConsole(stdi, inputBuf, (128 / sizeof(TCHAR)), &numCharsRead, NULL)) {
        printf("OOpds\n");
        return OHNOES;
    }

    printf("Chars read: %s\n", inputBuf);

    return ALLGOOD;
}
*/


/*
https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
*/
int CheckForConsoleInput() {
    INPUT_RECORD inputBuf[128];
    KEY_EVENT_RECORD ker;
    DWORD recordsRead, numEvents, fdwMode, fwdSaved;
    int loopCount = 0;
    COORD c = { 20, 20 };

    GetNumberOfConsoleInputEvents(STDI, &numEvents);
    if (numEvents == 0) {
        //Nothing to do here, just set curInput and leave
        curInput = none;
        return ALLGOOD;
    }

    if (!ReadConsoleInput(STDI, inputBuf, 1, &recordsRead)){
        printf("NO!!\n");
        return OHNOES; 
    }

    while (loopCount++ <= 100)
    {
        for (int i = 0; i < recordsRead; i++)
        {
            if (inputBuf[i].EventType == KEY_EVENT) { 
                ker = inputBuf[i].Event.KeyEvent;
                if (ker.bKeyDown) {
                    switch (ker.wVirtualKeyCode) {
                    case VK_LEFT:
                    case 'A':
                        curInput = left;
                        curInputs |= left;
                        break;
                    case VK_RIGHT:
                    case 'D':
                        curInput = right;
                        curInputs |= right;
                        break;
                    case VK_UP:
                    case 'W':
                        curInput = up;
                        curInputs |= up;
                        break;
                    case VK_DOWN:
                    case 'S':
                        curInput = down;
                        curInputs |= down;
                        break;
                    case VK_SPACE:
                        curInput = shoot;
                        curInputs |= shoot;
                        break;
                    case 'Q':
                        curInput = quit;
                        curInputs |= quit;
                        break;
                    case VK_ESCAPE:
                        curInput = pause;
                        curInputs |= pause;
                    default:
                        //printf("NO!!");
                        return OHNOES;
                    }
                }
                else {
                    switch (ker.wVirtualKeyCode) {
                    case VK_LEFT:
                    case 'A':
                        curInputs &= !left;
                        break;
                    case VK_RIGHT:
                    case 'D':
                        curInputs &= !right;
                        break;
                    case VK_UP:
                    case 'W':
                        curInputs &= !up;
                        break;
                    case VK_DOWN:
                    case 'S':
                        curInputs &= !down;
                        break;
                    case VK_SPACE:
                        curInputs &= !shoot;
                        break;
                    case 'Q':
                        curInputs &= !quit;
                        break;
                    case VK_ESCAPE:
                        curInputs &= !pause;
                    default:
                        //printf("NO!!");
                        return OHNOES;
                    }
                }
            }

            
        }
    }

    return ALLGOOD;
}


WORD GetInputKeyCode() {
    INPUT_RECORD inputBuf[128];
    KEY_EVENT_RECORD ker;
    DWORD recordsRead, fdwMode, fwdSaved;
    int loopCount = 0;
    HANDLE stdo = GetStdHandle(STANDARDOUT);
    COORD c = { 20, 20 };

    if (!ReadConsoleInput(
        STDI,      // input buffer handle
        inputBuf,     // buffer to read into
        128,         // size of read buffer
        &recordsRead)) // number of records read
    {
        printf("NO!!\n");
        return OHNOES;
    }

    while (loopCount++ <= 100)
    {
        // Dispatch the events to the appropriate handler.
        for (int i = 0; i < recordsRead; i++)
        {
            switch (inputBuf[i].EventType)
            {
            case KEY_EVENT: // keyboard input
                ker = inputBuf[i].Event.KeyEvent;
                SetConsoleCursorPosition(stdo, c);
                printf("Pressed :%x\n", ker.wVirtualKeyCode);
                return inputBuf[i].Event.KeyEvent.wVirtualKeyCode;
                //keeping the break here on principle...
                break;

            default:
                printf("Unknown event type\n");
                return OHNOES;
                break;
            }
        }
    }
    return 0; //There is no 0 key code BAD!!
}







/*
Lots of help from:
https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
*/

/*
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
VOID ErrorExit(LPSTR);


int CheckForConsoleInput() {
    
    HANDLE stdh = GetStdHandle(STANDARDOUT);
    INPUT_RECORD inputBuf[128];
    DWORD recordsRead, fdwMode, fwdSaved;
    int loopCount = 0;

    GetConsoleMode(stdh, &fwdSaved);
    fdwMode =  ENABLE_WINDOW_INPUT;// | ENABLE_MOUSE_INPUT;
    SetConsoleMode(stdh, fdwMode);

    if (!ReadConsoleInput(
        stdh,      // input buffer handle
        inputBuf,     // buffer to read into
        128,         // size of read buffer
        &recordsRead)) // number of records read
    {
        printf("NO!!\n");
    }
       

    while (loopCount++ <= 100)
    {
        //printf("recordsRead: %d\n", recordsRead);
        // Dispatch the events to the appropriate handler.
        for (int i = 0; i < recordsRead; i++)
        {
            printf("wat");
            switch (inputBuf[i].EventType)
            {
            case KEY_EVENT: // keyboard input
                KeyEventProc(inputBuf[i].Event.KeyEvent);
                break;

            case MOUSE_EVENT: // mouse input
                MouseEventProc(inputBuf[i].Event.MouseEvent);
                break;

            case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
                ResizeEventProc(inputBuf[i].Event.WindowBufferSizeEvent);
                break;

            case FOCUS_EVENT:  // disregard focus events

            case MENU_EVENT:   // disregard menu events
                break;

            default:
                //ErrorExit("Unknown event type");
                break;
            }
        }
    }

    SetConsoleMode(stdh, fwdSaved);
    return ALLGOOD;
}

VOID ErrorExit(LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    //SetConsoleMode(stdh, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    printf("Key event: ");

    if (ker.bKeyDown)
        printf("key pressed\n");
    else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    printf("Mouse event: ");

    switch (mer.dwEventFlags)
    {
    case 0:
        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            printf("left button press \n");
        }
        else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
        {
            printf("right button press \n");
        }
        else
        {
            printf("button press\n");
        }
        break;
    case DOUBLE_CLICK:
        printf("double click\n");
        break;
    case MOUSE_HWHEELED:
        printf("horizontal mouse wheel\n");
        break;
    case MOUSE_MOVED:
        printf("mouse moved\n");
        break;
    case MOUSE_WHEELED:
        printf("vertical mouse wheel\n");
        break;
    default:
        printf("unknown\n");
        break;
    }
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    printf("Resize event\n");
    printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}


*/

