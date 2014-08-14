/*******************************************************************************
 *  warp.cpp
 *
 *  This file defines the functions that control the behavior of the player
 *  warping 'up' or 'down'.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                    WARP UP
--------------------------------------------------------------------------------
 *  Start warping up
*/
void warp_up( void )
{
    /*  Adjust warp speed target and set warping to true */
    maxWarpSpeed = 15;
    warp = true;
}


/*
--------------------------------------------------------------------------------
                                   WARP DOWN
--------------------------------------------------------------------------------
 *  Start warping down
*/
void warp_down( void )
{
    /*  Adjust warp speed target and set warping to false */
    maxWarpSpeed = 1;
    warp = true;
}


/*
--------------------------------------------------------------------------------
                                  WARP UPDATE
--------------------------------------------------------------------------------
 *  Handles the gradual speeding up of the player during warp.  currentScore is
 *  used as a metric since it's constantly ticking up anyway, and can be relied
 *  upon to give even results from frame to frame compared to something like
 *  SDL_GetTicks().
*/
void warp_update( void )
{
    /*  Every half second (approx), warp speed up if we're below max speed */
    if( warpSpeed < maxWarpSpeed && currentScore % 30 == 0 )
        ++warpSpeed;

    /*  Every 1/15 of a second (approx), warp speed down if we're above max */
    else if( warpSpeed > maxWarpSpeed && currentScore % 4 == 0 )
        --warpSpeed;

    /*  Otherwise, if we've reached the target speed, disable warp */
    else if( warpSpeed == maxWarpSpeed )
        warp = false;
}
