#include "globals.h"

char **board;
Player player;

void initPlayer()
{
    player.boardHeight = 0;
    player.branchWidth = 4;
    player.earnRatio = 1;
    player.freeze = 0;
    player.treedata[0] = NULL;
    player.treedata[1] = NULL;
    player.playerHeight = 3;
    player.playerPos = 'L';
    player.speed = 1;
    player.speedRemain = 0;
    player.time = 8;
    player.treeWidth = 3;
}
