#include "menu.h"

#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "code.h"

static void newGame()
{
    char change;

    Byte boardHeight;
    Byte playerHeight;
    Byte branchWidth;
    Byte treeWidth;

    initPlayer();

    printf("Do you want to change preferences? (yY, nN) ");
    scanf("%c", &change);

    if (change == 'y' || change == 'Y')
    {
        printf("Enter board height : ");
        scanf("%u", &boardHeight);
        printf("Enter branch width : ");
        scanf("%u", &branchWidth);
        printf("Enter tree width : ");
        scanf("%u", &treeWidth);

        player.boardHeight = boardHeight;
        player.branchWidth = branchWidth;
        player.treeWidth = treeWidth;
    }

    player.treedata[0] = malloc(player.boardHeight * sizeof(Byte));
    player.treedata[1] = malloc(player.boardHeight * sizeof(Byte));

    memset(player.treedata[0], 0, player.boardHeight);
    memset(player.treedata[1], 0, player.boardHeight);

    board = malloc(player.boardHeight * (player.treeWidth + (2 * player.branchWidth)) * sizeof(char *));

    for (int i = 0; i < player.boardHeight * (player.treeWidth + (2 * player.branchWidth)); i++)
    {
        // for string member
        board[i] = malloc(7 * sizeof(char));
    }

    printf(CLS_SCREEN);
}

static int loadGame()
{
    FILE *loadFile = NULL;
    Byte *loadData = malloc(sizeof(Player));
    Byte *loadDataArr[2] = {NULL, NULL};

    loadFile = fopen("save.bin", "rb");

    if (loadFile == NULL)
    {
        printf("Save file not found!\n");

        return 1;
    }
    

    if (fread(loadData, sizeof(Player), 1, loadFile) == 0)
    {
        printf("Save file is void\n");

        return 2;
    };

    Player *playerTempPtr = (Player *)modDecode(loadData, sizeof(Player), 12);
    player = *playerTempPtr;

    loadDataArr[0] = malloc(player.boardHeight);
    loadDataArr[1] = malloc(player.boardHeight);

    if (fread(loadDataArr[0], player.boardHeight, 1, loadFile) == 0 || fread(loadDataArr[1], player.boardHeight, 1, loadFile) == 0)
    {
        printf("Can not read necessary data");

        return 2;
    }

    player.treedata[0] = modDecode(loadDataArr[0], player.boardHeight, 12);
    player.treedata[1] = modDecode(loadDataArr[1], player.boardHeight, 12);

    fclose(loadFile);

    free(loadData);
    free(loadDataArr[0]);
    free(loadDataArr[1]);
    free(playerTempPtr);

    board = malloc(player.boardHeight * (player.treeWidth + (2 * player.branchWidth)) * sizeof(char *));

    for (int i = 0; i < player.boardHeight * (player.treeWidth + (2 * player.branchWidth)); i++)
    {
        // for string member
        board[i] = malloc(7 * sizeof(char));
    }


    return 0;
}

void showMenu()
{
    char select = 0;

    while (select == 0)
    {
        printf(CLS_SCREEN);
        printf("Load or New? (lL, nN) ");
        scanf("%c", &select);

        switch (select)
        {
        case 'l':
        case 'L':
            printf(CLS_SCREEN);
            if (loadGame() != 0)
            {
                select = 0;

                usleep(1000000);
            }
            break;

        case 'n':
        case 'N':
            printf(CLS_SCREEN);
            newGame();
            break;

        default:
            select = 0;
            break;
        }
    }
}