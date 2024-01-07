#include "executeaction.h"

#include <stdio.h>
#include <stdlib.h>

static int maxAttackToNextEarnRatio = 10;
static char *itemName = "";

static void generateTree()
{
    Byte check = 1;

    for (Byte i = 1; i <= 3; i++)
    {
        if (player.treedata[0][i] == 1 || player.treedata[1][i] == 1)
        {
            check = 0;

            break;
        }
    }

    char branchInfo = 'N'; // 'L':left, 'R':right, 'N':nothing

    // add branch if condition is true
    if (check == 1)
    {
        int r = rand() % 10;

        if (r == 0) // probabality = %10
        {
            branchInfo = 'L';
            player.treedata[0][0] = 1;
        }
        else if (r == 1) // probabality = %10
        {
            branchInfo = 'R';
            player.treedata[1][0] = 1;
        }
    }

    // add item --- probabality = %5
    if ((rand() % 20) == 0)
    {
        int side = branchInfo == 'L' ? 1 : 0;

        player.treedata[side][0] = 2;
    }
}

static void swapDownTreeData()
{
    for (Byte i = player.boardHeight - 1; i > 0; i--)
    {
        player.treedata[0][i] = player.treedata[0][i - 1];
        player.treedata[1][i] = player.treedata[1][i - 1];
    }

    player.treedata[0][0] = 0;
    player.treedata[1][0] = 0;
}

static Status processAction(Action playerACtion)
{
    if (playerACtion == MoveLeft)
    {
        player.playerPos = 'L';
        ++player.attackCount;
        itemName = "";
        if (player.time + 1 <= 8)
        {
            ++player.time;
        }
        if (player.freeze > 0)
        {
            --player.freeze;
        }

        if (player.treedata[0][player.boardHeight - 1] == 1) // branch
        {
            return Loss;
        }
        else if (player.treedata[0][player.boardHeight - 1] == 2) // item
        {
            Item item = rand() % 4;

            switch (item)
            {
            case Speed:
                player.speed = 1.2;
                player.speedRemain = 5;
                itemName = "Speed";
                break;

            case Freeze:
                player.freeze = 10;
                itemName = "Freese";
                break;

            case Double:
                player.earnRatio *= 2;
                itemName = "Double";
                break;

            case Time:
                if (player.time + 2 >= 8)
                {
                    player.time = 8;
                }
                else
                {
                    player.time += 2;
                }
                itemName = "Time";
                break;

            default:
                break;
            }
        }

        if (maxAttackToNextEarnRatio - player.attackCount == 0)
        {
            player.earnRatio += 0.1;
            maxAttackToNextEarnRatio += 10 * player.earnRatio;
        }

        player.score += player.earnRatio;

        swapDownTreeData();
    }
    else if (playerACtion == MoveRight)
    {
        player.playerPos = 'R';
        ++player.attackCount;
        itemName = "";
        if (player.time + 1 <= 8)
        {
            ++player.time;
        }
        if (player.freeze > 0)
        {
            --player.freeze;
        }

        if (player.treedata[1][player.boardHeight - 2] == 1) // branch
        {
            return Loss;
        }
        else if (player.treedata[1][player.boardHeight - 2] == 2) // item
        {
            Item item = rand() % 4;

            switch (item)
            {
            case Speed:
                player.speed = 1.2;
                player.speedRemain = 5;
                itemName = "Speed";
                break;

            case Freeze:
                player.freeze = 10;
                itemName = "Freese";
                break;

            case Double:
                player.earnRatio *= 2;
                itemName = "Double";
                break;

            case Time:
                if (player.time + 2 >= 8)
                {
                    player.time = 8;
                }
                else
                {
                    player.time += 2;
                }
                itemName = "Time";
                break;

            default:
                break;
            }
        }

        if (maxAttackToNextEarnRatio - player.attackCount == 0)
        {
            player.earnRatio += 0.1;
            maxAttackToNextEarnRatio += 10 * player.earnRatio;
        }

        player.score += player.earnRatio;

        swapDownTreeData();
    }
    else if (playerACtion == Save)
    {
    }
    else // playerACtion == Quit
    {
        printf(DEFAULT);
        printf(DEL_SCREEN);
        exit(0);
    }

    return Normal;
}

static void drawBoard()
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
        else // draw left nothing
        {
            for (Byte j = 0; j < player.branchWidth; j++)
            {
                board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = SKY;
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
        else // draw right nothing
        {
            for (Byte j = player.branchWidth + player.treeWidth; j < player.treeWidth + (2 * player.branchWidth); j++)
            {
                board[_2Dto1D(i, j, player.treeWidth + (2 * player.branchWidth))] = SKY;
            }
        }
    }

    if (player.playerPos == 'L')
    {
        board[_2Dto1D(player.boardHeight - 1, player.branchWidth - 1, player.treeWidth + (2 * player.branchWidth))] = HUMAN_COLOR;
    }
    else // player.playerPos == 'R'
    {
        board[_2Dto1D(player.boardHeight - 1, player.branchWidth + player.treeWidth, player.treeWidth + (2 * player.branchWidth))] = HUMAN_COLOR;
    }
}

static void printScene()
{
    while(workingThread == 0);
    workingThread = 1;

    printf(MOVE_CURSOR(2, 1));
    printf(DEL_TOEND);
    printf(INFO);
    printf("Earn Ratio : %.1fX point --- (%d attack remain)\n", player.earnRatio, maxAttackToNextEarnRatio - player.attackCount);
    printf("Score : %d\n", player.score);
    printf("Help : aA=left, dD=right, qQ=quit\n\n");
    printf(SAVE_CURSOR);
    if (itemName != "")
    {
        printf(MOVE_CURSOR(2, 50)"*************************");
        printf(MOVE_CURSOR(3, 50)"* %s           ", itemName);
        printf(MOVE_CURSOR(4, 50)"*************************");
    }
    printf(RESTORE_CURSOR);
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
        printf(GROUND "  ");
    }

    printf(DEFAULT);

    workingThread = 2;
}

Status execAction(Action playerAction)
{
    Status status;

    if (playerAction != Start)
    {
        status = processAction(playerAction);

        if (status == Loss)
        {
            return Loss;
        }

        generateTree();
    }
    drawBoard();
    printScene();

    return Normal;
}