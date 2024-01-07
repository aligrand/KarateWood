#include "inputmanager.h"

#include <conio.h>

Action getAction()
{
    Action action;

    Byte whileStatus = 1;
    while (whileStatus)
    {
        char ch = getch();
        switch (ch)
        {
        case 'a':
        case 'A':
            action = MoveLeft;
            whileStatus = 0;
            break;

        case 'd':
        case 'D':
            action = MoveRight;
            whileStatus = 0;
            break;

        case 'q':
        case 'Q':
            action = Quit;
            whileStatus = 0;
            break;

        case 'g':
        case 'G':
            action = Save;
            whileStatus = 0;
            break;

        default:
            break;
        }
    }

    return action;
}