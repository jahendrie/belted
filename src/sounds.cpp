/*******************************************************************************
 *  sounds.cpp
 *
 *  This file defines the functions that control the toggling and muting of
 *  all sound effects and music.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  TOGGLE MUSIC
--------------------------------------------------------------------------------
 *  Toggles the music on or off
*/
void toggle_music( void )
{
    /*  If the music is playing, set the volume to zero and display the OSD */
    if( playMusic )
    {
        Mix_VolumeMusic( 0 );
        playMusic = false;
        osd( "MUSIC OFF" );
    }

    /*  If the music is not playing, turn it up */
    else
    {
        Mix_VolumeMusic( MIX_MAX_VOLUME );
        playMusic = true;
        osd( "MUSIC ON" );
    }
}



/*
--------------------------------------------------------------------------------
                                 TOGGLE SOUNDS
--------------------------------------------------------------------------------
 *  Toggles the sound effects on or off
*/
void toggle_sounds( void )
{
    /*  If the sounds are playing, turn all sfx to zero and display OSD */
    if( playSound )
    {
        Mix_Volume( -1, 0 );
        playSound = false;
        osd( "SOUND OFF" );
    }

    /*  Otherwise, turn them all to max volume */
    else
    {
        Mix_Volume( -1, MIX_MAX_VOLUME );
        playSound = true;
        osd( "SOUND ON" );
    }

}



/*
--------------------------------------------------------------------------------
                                      MUTE
--------------------------------------------------------------------------------
 *  Mutes all sound effects and music
*/
void mute( bool muting )
{
    /*  If we're told to mute, turn everything to zero volume */
    if( muting )
    {
        Mix_Volume( -1, 0 );
        Mix_VolumeMusic( 0 );
    }

    /*  If we're told to unmute, turn everything to max volume */
    else if( ! muting )
    {
        Mix_Volume( -1, MIX_MAX_VOLUME );
        Mix_VolumeMusic( MIX_MAX_VOLUME );
    }
}
