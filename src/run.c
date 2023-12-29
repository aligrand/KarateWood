#include "run.h"

#include <windows.h>
#include <stdio.h>

void runGame()
{
    Action playerAction = None;
    Status gameStatus = Normal;

    printf("\033[?25l");

    while (gameStatus == Normal)
    {
        system("cls");

        gameStatus = execAction(playerAction);

        Sleep(1000);
    } 
}