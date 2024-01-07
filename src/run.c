#include "run.h"

#include "inputmanager.h"
#include "executeaction.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

static void loseShow()
{
    printf(DEFAULT);

    printf(DEL_SCREEN);

    printf("------------\n"
            "YOU LOSE ...\n"
            "------------");
}

static void *timeProcess(void *arg)
{
    while (*(Status *)arg == Normal)
    {
        while(workingThread == 1);
        workingThread = 0;

        printf(MOVE_CURSOR(1, 1));
        printf(DEL_LINE);
        printf(INFO);
        printf("Time : %.3f s (Speed : %.3f)\n", player.time, player.speed);
        printf(DEFAULT);

        workingThread = 2;

        usleep(250000);

        if ((player.speedRemain - (0.25 * player.speed)) > 0)
        {
            player.speedRemain -= (0.25 * player.speed);
        }
        else
        {
            player.speed = 1;
        }

        if (player.freeze == 0)
        {
            if ((player.time - (0.25 * player.speed)) > 0)
            {
                player.time -= (0.25 * player.speed);
            }
            else
            {
                player.time = 0;
            }
        }

        if (player.time == 0)
        {
            loseShow();

            exit(0);
        }
    }

    pthread_exit(NULL);

    return NULL;
}

void runGame()
{
    Action playerAction = Start;
    Status gameStatus = Normal;
    pthread_t pthrID;

    printf("\033[?25l");

    srand(time(NULL));
    
    printf(DEL_SCREEN);
    printf(MOVE_CURSOR(0, 0));

    pthread_create(&pthrID, NULL, timeProcess, &gameStatus);

    while (gameStatus == Normal)
    {
        gameStatus = execAction(playerAction);
        playerAction = getAction();
    }

    loseShow();

    pthread_join(pthrID, NULL); 
}