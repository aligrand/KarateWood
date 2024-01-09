#pragma once

typedef unsigned char Byte;

#define NULL ((void *)0)

typedef enum 
{
    MoveRight,
    MoveLeft,
    Save,
    Quit,
    Start
} Action;

typedef enum
{
    Loss,
    Normal
} Status;

typedef enum
{
    Speed = 0,
    Freeze,
    Double,
    Time
} Item;

typedef struct
{
    Byte branchWidth;
    char playerPos; // 'L' : left & 'R' : right
    Byte *treedata[2]; // a dynamic 2D-array for data in edge of tree +++ 0 : nothing, 1 : branch, 2 : item
    Byte boardHeight;
    float time;
    float earnRatio;
    float speed;
    float speedRemain;
    Byte freeze;
    Byte treeWidth;
    int attackCount;
    int score;
} Player;

void initPlayer();

#define BRANCH_COLOR "\033[42m" // green
#define TREE_BODY_COLOR "\033[42m" // green
#define ITEM_COLOR "\033[43m" // yellow
#define HUMAN_COLOR "\033[100m" // bright black
#define SKY "\033[104m" // bright blue
#define GROUND "\033[47m" // white
#define DEFAULT "\033[49m" // default
#define INFO "\033[41m" // red
#define DESTROYED "\033[45m" // magenta
#define DEL_LINE "\033[1K\033[1;1H" // erase line in screen
#define DEL_TOEND "\033[0J" // erase from cursor until end of screen
#define CLS_SCREEN "\033[2J\033[1;1H" // erase screen and go to first of terminal
#define MOVE_CURSOR(line, col) "\033["#line";"#col"H" // move cursor in screen
#define SAVE_CURSOR "\033[s" // save position of cursor
#define RESTORE_CURSOR "\033[u" // restore last saved cursor position

extern char **board;
extern Player player;
extern Byte workingThread; // 0: thread, 1:main thread, 2:nothing

#define _2Dto1D(i, j, width) (((i) * (width)) + (j))