/*******************************************************************************
 *  reset.cpp
 *
 *  This file defines the reset function, which respawns the player character
 *  and resets his stats, as well as resets a number of other important things
 *  needed to give the player a fresh start after every game over.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif

void reset( void )
{
    /*  Reset player */
    player.reset_stats();

    /*  Reset enemies */
    enemies.clear();
    enemyDelay = -90;

    /*  Reset scores */
    currentScore = 0;
    chargeScore = 0;
    extraLifeScore = 0;

    /*  Turn off the new flag on the high score screen */
    gScores->set_new( false );

    /*  Stop the 'tail' */
    tail.stop_tail();

    /*  Stop the music */
    if( Mix_PlayingMusic() == 1 )
        Mix_HaltMusic();

    /*  Start the music over again */
    if( Mix_PlayMusic( musicMain, -1 ) == -1 )
    {
        printf("WARNING:  Could not play main theme:  %s\n",
                Mix_GetError() );
    }
}
