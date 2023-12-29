#include "menu.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void newGame()
{
    Byte height;

    initPlayer();

    printf("Enter height : ");
    scanf("%u", &height);

    player.boardHeight = height;

    player.treedata[0] = malloc(height * sizeof(Byte));
    player.treedata[1] = malloc(height * sizeof(Byte));

    memset(player.treedata[0], 0, player.boardHeight);
    memset(player.treedata[1], 0, player.boardHeight);

    board = malloc(player.boardHeight * (player.treeWidth + (2 * player.branchWidth)) * sizeof(char *));

    for (int i = 0; i < player.boardHeight * (player.treeWidth + (2 * player.branchWidth)); i++)
    {
        board[i] = malloc(7 * sizeof(char));
    }

    system("cls");
}

void showMenu()
{
    newGame();
}