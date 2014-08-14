/*==============================================================================
 *  Belted  |   Version 0.92    |   zlib license    |   2014-07-07
 *  James Hendrie               |   hendrie.james@gmail.com
 *                              |   http://www.someplacedumb.net/games
 *
 *  Belted is an arcade-style game designed to waste your time in 30-second
 *  increments between downloads or whatever else it is you're waiting for.
 *
 *  Code and art by James Hendrie.  Both are licensed under the zlib license
 *  (http://www.gzip.org/zlib/zlib_license.html).  See COPYING.txt for more
 *  details.
 *
 *  The music is by Kevin MacLeod (http://www.incompetech.com), licensed under
 *  the Creative Commons:  By Attribution 3.0 license.  See CREDITS.txt for
 *  more info.
 *
 *  Almost all of the sound assets were gathered from http://www.freesound.org.
 *  See CREDITS.txt for more info.
 *
 *                                                  Initial release:  2014-06-30
  ============================================================================*/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                      MAIN
--------------------------------------------------------------------------------
*/
int main( int argc, char *argv[] )
{
    /*  First off, check the args */
    int aReturn = check_args( argc, argv );

    /*  Might seem weird but just go with it man */
    if( aReturn == -1 )
        return( 0 );
    else if( aReturn == 1 )
        return( 1 );

    /*  Init SDL and its subsystems */
    if( ! init() )
    {
        printf("ERROR:  Could not init SDL and/or its subsystems.\n");
        return(1);
    }

    /*  Load the fonts */
    if( ! load_fonts() )
    {
        printf("ERROR:  Couldn't load fonts\n");
        return(1);
    }


    /*  Load the media */
    if( ! load_media() )
    {
        printf("ERROR:  Could not load media.\n");
        return(1);
    }

    /*  Load the menu screen */
    if( ! load_menu() )
    {
        printf("ERROR:  Could not load menu screen\n");
        return(1);
    }

    /*  Load the initials */
    if( ! load_initials() )
    {
        printf("ERROR:  Could not load initials\n");
        return(1);
    }

    /*  Load the help screen */
    if( ! load_help() )
    {
        printf("ERROR:  Help screen initialization failed\n");
        return( 1 );
    }

    /*  Load the credits screen */
    if( ! load_credits() )
    {
        printf("ERROR:  Could not load the credits screen\n");
        return( 1 );
    }

    /*  Init the player */
    load_player();

    /*  Load the star field */
    load_starfield();

    /*  Init the panel */
    load_panel();

    /*  Load the scores */
    load_scores();

    /*  Give the scores their first update */
    gScores->update();

    /*  Create event queue struct */
    SDL_Event e;

    /*  Grab mouse */
    SDL_SetRelativeMouseMode( SDL_TRUE );

    /*  Play the menu theme right off the bat if music is allowed */
    if( playMusic )
    {
        if( Mix_PlayMusic( musicMenu, -1 ) == -1 )
        {
            printf("WARNING:  Could not play menu theme:  %s\n",
                    Mix_GetError() );
        }
    }

    /*  While the player hasn't elected to quit */
    while( quit == false )
    {
        /*  Handle all events */
        handle_events( e );

        /*  Update everything */
        update();

        /*  Draw the window background */
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );

        /*  Render everything else */
        render();

        /*  Show what's been rendered */
        SDL_RenderPresent( gRenderer );

        /*  Basic delay */
        if( limitFPS )
            SDL_Delay( 1000 / FPS );
    }

    /*  Close everything out */
    close();

    return(0);
}
