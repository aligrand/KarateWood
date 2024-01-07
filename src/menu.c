#include "menu.h"

#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        board[i] = malloc(7 * sizeof(char));
    }

    printf(DEL_SCREEN);
}

void showMenu()
{
    newGame();
}