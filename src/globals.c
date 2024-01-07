#include "globals.h"

char **board;
Player player;
Byte workingThread;

void initPlayer()
{
    player.boardHeight = 10;
    player.branchWidth = 4;
    player.earnRatio = 1;
    player.freeze = 0;
    player.treedata[0] = NULL;
    player.treedata[1] = NULL;
    player.playerPos = 'L';
    player.speed = 1;
    player.speedRemain = 0;
    player.time = 8;
    player.treeWidth = 3;
    player.attackCount = 0;
    player.score = 0;
}
