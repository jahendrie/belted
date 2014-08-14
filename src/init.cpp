/*******************************************************************************
 *  init.cpp
 *
 *  This file defines all of the main SDL initialization functions.  It also
 *  does a couple of other 'init-y' things that I couldn't fit elsewhere.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                   INIT COLOR
--------------------------------------------------------------------------------
 *  This function initializes an individual color.  It's only here because I
 *  didn't want to compile with -std=c++11.
*/
SDL_Color init_color( Uint8 r, Uint8 g, Uint8 b )
{
    SDL_Color color = { r, g, b, 255 };

    return( color );
}



/*
--------------------------------------------------------------------------------
                                  INIT COLORS
--------------------------------------------------------------------------------
 *  This inits all of the colors used in the global colors array.
*/
void init_colors( void )
{
    colors[ COLOR_WHITE ] = init_color( 255, 255, 255 );
    colors[ COLOR_RED ] = init_color( 255, 0, 0 );
    colors[ COLOR_GREEN ] = init_color( 0, 255, 0 );
    colors[ COLOR_BLUE ] = init_color( 0, 0, 255 );
    colors[ COLOR_YELLOW ] = init_color( 255, 255, 0 );
    colors[ COLOR_VIOLET ] = init_color( 255, 0, 255 );
    colors[ COLOR_CYAN ] = init_color( 0, 255, 255 );
    colors[ COLOR_ORANGE ] = init_color( 255, 127, 0 );
    colors[ COLOR_HOT_PINK ] = init_color( 255, 0, 127 );
    colors[ COLOR_LIME ] = init_color( 127, 255, 0 );
    colors[ COLOR_BLACK ] = init_color( 0, 0, 0 );
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Master init function.  Being a game made in SDL2, SDL2 and its subsystems
 *  are obviously critical to the functionality of the program.  Also, their
 *  initialization is kept here because it's tidier.
*/
bool init( void )
{
    /*  Init SDL */
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf("ERROR:  Could not init SDL.  SDL Error:  %s\n",
                SDL_GetError() );
        return( false );
    }

    /*  Init SDL_image */
    if( ( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) == false )
    {
        printf("ERROR:  Could not init SDL_image.  IMG Error:  %s\n",
                IMG_GetError() );
        return( false );
    }

    /*  Init SDL_mixer */
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf("ERROR:  Could not init SDL_mixer.  Mix Error:  %s\n",
                Mix_GetError() );
        return( false );
    }


    /*  Init SDL_ttf */
    if( TTF_Init() == -1 )
    {
        printf("ERROR:  Could not init SDL_ttf.  TTF Error:  %s\n",
                TTF_GetError() );
        return( false );
    }


    /*  Create our window */
    gWindow = SDL_CreateWindow( "BELTED (working title)",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf("ERROR:  Could not create window.  SDL Error:  %s\n",
                SDL_GetError() );
        return( false );
    }

    /*
     *  Create the renderer
     *
     *  We check for the limiting of FPS as a futureproofing thing.  Also,
     *  theoretically a bug-solving or performance thing.
     */

    /*  If they want to limit FPS, don't vsync */
    if( limitFPS )
        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

    /*  Otherwise, use vsync */
    else
    {
        gRenderer = SDL_CreateRenderer( gWindow, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    }
    if( gRenderer == NULL )
    {
        printf("ERROR:  Could not create renderer.  SDL Error:  %s\n",
                SDL_GetError() );
        return( false );
    }


    /*  Just for shits and giggles, we'll seed random here */
    srand( (unsigned int)time(NULL) );

    /*  Init boundary dimensions */
    BWIDTH = WWIDTH;
    BHEIGHT = WHEIGHT - 100;

    /*  Init colors */
    init_colors();

    /*  Init blend mode */
    SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );

    /*  Init transitions */
    init_transition();


    /*  If we made it this far, we're golden */
    return( true );
}
