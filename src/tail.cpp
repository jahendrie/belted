/*******************************************************************************
 *  tail.cpp
 *
 *  This file defines the tail class, which handles the colorful beam of light
 *  that trails the player while they're powered up.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
*/
Tail::Tail( void )
{
    init_tail();

}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Tail::~Tail( void )
{
    init_tail();
}



/*
--------------------------------------------------------------------------------
                                   INIT TAIL
--------------------------------------------------------------------------------
 *  This method initialized the tail and is called by both the constructor and
 *  the destructor.
*/
void Tail::init_tail( void )
{
    mActive = false;
    mFading = false;
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  This method keeps the tail in its correct place -- that is, trailing the
 *  player's position.
*/
void Tail::update( void )
{
    /*  Correct X and Y positions */
    mPos.x = player.get_pos_x();
    mPos.y = player.get_pos_y() + player.get_height() - 8;
}




/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Tail::render( void )
{
    /*  Length of the tail */
    int y = BHEIGHT;

    /*  Grab a pointer to the player's 'special' color */
    SDL_Color *playerColor = player.get_special_color();

    /*  Set the colors for the left half */
    Uint8 r = playerColor->r;
    Uint8 g = playerColor->g;
    Uint8 b = playerColor->b;
    Uint8 a = 127;

    /*  Left half */
    for( int x = mPos.x + 24; x < mPos.x + (player.get_width()/2) + 1; ++x )
    {
        SDL_SetRenderDrawColor( gRenderer, r, g, b, a );
        SDL_RenderDrawLine( gRenderer, x, mPos.y, x, y );

        /*  Adjust color / alpha channels */
        ++r;
        ++g;
        ++b;
        ++a;
    }

    /*   Reset the colors for the right half */
    r = playerColor->r;
    g = playerColor->g;
    b = playerColor->b;
    a = 127;

    /*  Right half */
    for( int x = (mPos.x + player.get_width()) - 20;
            x > mPos.x + (player.get_width()/2) - 1; --x )
    {
        SDL_SetRenderDrawColor( gRenderer, r, g, b, a );
        SDL_RenderDrawLine( gRenderer, x, mPos.y, x, y );

        /*  Adjust color / alpha channels */
        ++r;
        ++g;
        ++b;
        ++a;
    }
}



/*
--------------------------------------------------------------------------------
                            SET / GET ACTIVE STATUS
--------------------------------------------------------------------------------
*/
void Tail::set_active( bool active )
{
    mActive = active;
}

bool Tail::is_active( void )
{
    return( mActive );
}



/*
--------------------------------------------------------------------------------
                             START OR STOP THE TAIL
--------------------------------------------------------------------------------
*/
void Tail::start_tail( void )
{
    init_tail();

    mActive = true;
    mFading = false;
}

void Tail::start_fading( void )
{
    mActive = false;
    mFading = true;
}

void Tail::stop_tail( void )
{
    init_tail();
    mFading = false;
    mActive = false;
}



/*
--------------------------------------------------------------------------------
                                   IS FADING
--------------------------------------------------------------------------------
*/
bool Tail::is_fading( void )
{
    return( mFading );
}
