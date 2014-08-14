/*******************************************************************************
 *  transition.cpp
 *
 *  This file defines the functions used to handle transitions from one screen
 *  to another.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                              SET FUNCTION POINTER
--------------------------------------------------------------------------------
 *  This function returns a function pointer that points to one of the rendering
 *  functions defined in render.cpp (and declared in prototypes.h).  Which
 *  rendering function pointer is returned depends on the given screen.
*/
void (* set_function_pointer( int screen ))( void )
{
    switch( screen )
    {
        case SCREEN_MENU:
            return( &render_menu );
            break;
        case SCREEN_MAIN:
            return( &render_main );
            break;
        case SCREEN_GAME_OVER:
            return( &render_game_over );
            break;
        case SCREEN_HIGH_SCORES:
            return( &render_high_scores );
            break;
        case SCREEN_ENTER_HIGH_SCORE:
            return( &render_enter_high_score );
            break;
        case SCREEN_HELP:
            return( &render_help );
            break;
        case SCREEN_CREDITS:
            return( &render_credits );
            break;
        default:
            return( NULL );
    }
}


/*
--------------------------------------------------------------------------------
                                INIT TRANSITION
--------------------------------------------------------------------------------
 *  This function initializes the global transition struct with all of the
 *  information it needs to start its magical journey.
*/
void init_transition( void )
{
    transition.maxTicks = 60;               //  Max ticks
    transition.ticks = 0;                   //  Current ticks
    transition.started = false;             //  Whether transition has started
    transition.velocity = 0;                //  Current velocity
    transition.x = transition.y = 0;        //  X and Y position
    transition.w = WWIDTH;                  //  Width
    transition.h = WHEIGHT;                 //  Height

}


/*
--------------------------------------------------------------------------------
                       TRANSITION MOVEMENT INITIALIZATION
--------------------------------------------------------------------------------
 *  This function mainly draws everything from the two relevant screens (the
 *  screen being transitioned from and the screen being transitioned to) to the
 *  'blank' target textures.  It also sets the actual rendering of the
 *  transition into motion by incrementing transition.ticks.
*/
void transition_movement_init( void )
{
        /*  Get our function pointers */
        void (*transition_from)(void) = set_function_pointer( transition.from );
        void (*transition_to)(void) = set_function_pointer( transition.to );

        /*  Set render target to first blank texture */
        SDL_SetRenderTarget( gRenderer, transTexture1 );

        /*  Clear the background of said blank texture */
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );

        /*  Render all of the stuff from the 'from' screen to the texture */
        transition_from();

        /*  Now set the render target to the second blank texture */
        SDL_SetRenderTarget( gRenderer, transTexture2 );

        /*  Clear the background of said blank texture */
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );

        /*  Render the upcoming screen to the next texture */
        transition_to();

        /*  Reset render target to the default */
        SDL_SetRenderTarget( gRenderer, NULL );

        /*  Render the 'from' texture again to prevent flicker */
        transition_from();

        /*  Increment the ticks to move on */
        ++transition.ticks;
}



/*
--------------------------------------------------------------------------------
                              VERTICAL TRANSITION
--------------------------------------------------------------------------------
 *  This is the up/down transition function.
*/
void transition_vertical( int direction )
{
    /*  If it has just started */
    if( transition.started && transition.ticks == 0 )
        transition_movement_init();

    /*  If it hasn't just started but isn't yet over */
    else if( transition.ticks <
            transition.maxTicks )
    {
        /*  We grab this here so we can use it for both textures */
        SDL_Rect r = { transition.x, transition.y, transition.w, transition.h };

        /*  Render the transition textures */
        SDL_RenderCopy( gRenderer, transTexture1, NULL, &r );

        /*  Set the Y position for the second texture */
        r.y += ( WHEIGHT * ( -direction ) );

        /*  Render the second transition texture */
        SDL_RenderCopy( gRenderer, transTexture2, NULL, &r );


        /*  Reset transition / game state when the transition is over */
        if( transition.y <= ( -WHEIGHT ) || transition.y >= WHEIGHT )
        {
            /*  End and reset the transition */
            init_transition();

            /*  Set the screen to where it needs to be */
            currentScreen = transition.to;
        }
        else
        {
            /*  Move the texture up or down at an increasing speed */
            transition.y += transition.velocity * direction;

            /*  Increase the absolute velocity */
            transition.velocity += 2;
        }
    }
}



/*
--------------------------------------------------------------------------------
                             HORIZONTAL TRANSITION
--------------------------------------------------------------------------------
 *  This is the left/right transition.
*/
void transition_horizontal( int direction )
{
    /*  If it has just started */
    if( transition.started && transition.ticks == 0 )
        transition_movement_init();

    /*  If it hasn't just started but isn't yet over */
    else if( transition.ticks <
            transition.maxTicks )
    {
        /*  We grab this here so we can use it for both textures */
        SDL_Rect r = { transition.x, transition.y, transition.w, transition.h };

        /*  Render the transition textures */
        SDL_RenderCopy( gRenderer, transTexture1, NULL, &r );

        /*  Set the Y position for the second texture */
        r.x += ( WWIDTH * ( -direction ) );

        /*  Render the second transition texture */
        SDL_RenderCopy( gRenderer, transTexture2, NULL, &r );


        /*  Reset transition / game state when the transition is over */
        if( transition.x <= ( -WWIDTH ) || transition.x >= WWIDTH )
        {
            /*  End and reset the transition */
            init_transition();

            /*  Set the screen to where it needs to be */
            currentScreen = transition.to;
        }
        else
        {
            /*  Move the texture up or down at an increasing speed */
            transition.x += transition.velocity * direction;

            /*  Increase the absolute velocity */
            transition.velocity += 2;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                START TRANSITION
--------------------------------------------------------------------------------
 *  This is the function called from other places in the program to kick things
 *  off and get the transition in motion.
*/
void start_transition( int toScreen, int directionKey )
{
    /*  Set our transition target screen IDs */
    transition.from = currentScreen;
    transition.to = toScreen;

    /*  Set current screen to SCREEN_TRANSITION */
    currentScreen = SCREEN_TRANSITION;

    /*  Set transition directio and started bool */
    transition.direction = directionKey;
    transition.started = true;

    /*  Send the current ticks to the misc ticks */
    miscTicks = SDL_GetTicks();

    Mix_PlayChannel( -1, soundEffectTransition, 0 );
}




/*
--------------------------------------------------------------------------------
                               RENDER TRANSITION
--------------------------------------------------------------------------------
 *  This is called from the main render function in render.cpp.  Guess what it
 *  does.
*/
void render_transition( void )
{
    switch( transition.direction )
    {
        case DIRECTION_LEFT:
            transition_horizontal( -1 );
            break;
        case DIRECTION_RIGHT:
            transition_horizontal( 1 );
            break;
        case DIRECTION_UP:
            transition_vertical( -1 );
            break;
        case DIRECTION_DOWN:
            transition_vertical( 1 );
            break;
    }
}
