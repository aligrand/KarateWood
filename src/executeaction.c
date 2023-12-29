#include "executeaction.h"

#include <stdio.h>
#include <stdlib.h>

void generateTree()
{
}

void processAction(Action playerACtion)
{
}

void drawBoard()
{
    for (Byte i = 0; i < player.boardHeight; i++)
    {
        // draw tree
        for (Byte j = player.branchWidth; j < player.branchWidth + player.treeWidth; j++)
        {
            board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = TREE_BODY_COLOR;
        }

        if (player.treedata[0][i] == 1) // draw left branch
        {
            for (Byte j = 0; j < player.branchWidth; j++)
            {
                board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = BRANCH_COLOR;
            }
        }
        else if (player.treedata[0][i] == 2) // draw left item
        {
            board[_2Dto1D(i, player.branchWidth, player.treeWidth + (2 * player.branchWidth))] = ITEM_COLOR;
        }
        else if (player.treedata[0][i] == 3) // draw left destroyed
        {
            board[_2Dto1D(i, player.branchWidth, player.treeWidth + (2 * player.branchWidth))] = DESTROYED;
        }
        else // draw left nothing
        {
            for (Byte j = 0; j < player.branchWidth; j++)
            {
                board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = BACKGROUND;
            }
        }

        if (player.treedata[1][i] == 1) // draw right branch
        {
            for (Byte j = player.branchWidth + player.treeWidth; j < player.treeWidth + (2 * player.branchWidth); j++)
            {
                board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = BRANCH_COLOR;
            }
        }
        else if (player.treedata[1][i] == 2) // draw right item
        {
            board[_2Dto1D(i, player.branchWidth + player.treeWidth - 1, player.treeWidth + (2 * player.branchWidth))] = ITEM_COLOR;
        }
        else if (player.treedata[1][i] == 3) // draw right destroyed
        {
            board[_2Dto1D(i, player.branchWidth + player.treeWidth - 1, player.treeWidth + (2 * player.branchWidth))] = DESTROYED;
        }
        else // draw right nothing
        {
            for (Byte j = player.branchWidth + player.treeWidth; j < player.treeWidth + (2 * player.branchWidth); j++)
            {
                board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = BACKGROUND;
            }
        }
    }

    if (player.playerPos == 'L')
    {
        for (Byte i = 1; i <= player.playerHeight; i++)
        {
            board[_2Dto1D(player.boardHeight - i, player.branchWidth - 1, player.treeWidth + (2 * player.branchWidth))] = HUMAN_COLOR;
        }
    }
    else // player.playerPos == 'R'
    {
        for (Byte i = 1; i <= player.playerHeight; i++)
        {
            board[_2Dto1D(player.boardHeight - i, player.branchWidth + player.treeWidth, player.treeWidth + (2 * player.branchWidth))] = HUMAN_COLOR;
        }
    }
}

void printScene()
{
    printf(INFO);
    printf("Time : %d s\n", player.time);
    printf("Earn Ratio : %d point\n\n", player.earnRatio);
    printf(DEFAULT);

    for (Byte i = 0; i < player.boardHeight; i++)
    {
        for (Byte j = 0; j < player.treeWidth + (2 * player.branchWidth); j++)
        {
            printf("%s  ", board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))]); // print 2-SPACE with color
        }

        printf("\n");
    }
    for (Byte i = 0; i < player.treeWidth + (2 * player.branchWidth); i++)
    {
        printf(GROUND"  ");
    }

    printf(DEFAULT);
}

Status execAction(Action playerAction)
{
    drawBoard();
    printScene();

    return Normal;
}