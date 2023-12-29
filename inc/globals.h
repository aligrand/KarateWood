#pragma once

typedef unsigned char Byte;

#define NULL ((void *)0)

typedef enum 
{
    MoveRight,
    MoveLeft,
    Attack,
    Save,
    Quit,
    None
} Action;

typedef enum
{
    Win,
    Loss,
    Exit,
    Normal
} Status;

typedef struct
{
    Byte branchWidth;
    char playerPos; // 'L' : left & 'R' : right
    Byte *treedata[2]; // a dynamic 2D-array for data in edge of tree +++ 0 : nothing, 1 : branch, 2 : item, 3 : destroyed
    Byte playerHeight;
    Byte boardHeight;
    Byte time;
    Byte earnRatio;
    float speed;
    Byte speedRemain;
    Byte freeze;
    Byte treeWidth;
} Player;

void initPlayer();

#define BRANCH_COLOR "\033[42m" // green
#define TREE_BODY_COLOR "\033[42m" // green
#define ITEM_COLOR "\033[43m" // yellow
#define HUMAN_COLOR "\033[100m" // bright black
#define BACKGROUND "\033[104m" // bright blue
#define GROUND "\033[47m" // white
#define DEFAULT "\033[49m" // default
#define INFO "\033[41m" // red
#define DESTROYED "\033[45m" // magenta

extern char **board;
extern Player player;

#define _2Dto1D(i, j, width) (((i) * (width)) + (j))