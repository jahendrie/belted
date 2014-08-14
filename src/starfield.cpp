/*******************************************************************************
 *  starfield.cpp
 *
 *  This file defines the starfield class, which handles the moving stars
 *  'under' the player / asteroids during gameplay.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
 *  When the starfield is initially created
*/
Starfield::Starfield( void )
{
    /*  Go through every available pixel on the screen */
    for( int row = 0; row < BHEIGHT; ++row )
    {
        for( int col = 0; col < BWIDTH; ++col )
        {
            /*  Approx. 1 in 1000 chance of there being a star */
            if( rand() % 1000 == 0 )
                add_star( col, row );
        }
    }
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Starfield::~Starfield( void )
{
    /*  Clear away all the stars */
    mStars.clear();
}


/*
--------------------------------------------------------------------------------
                                    ADD STAR
--------------------------------------------------------------------------------
 *  This method adds a star struct to the stars vector, defining a few key
 *  attributes of the star before doing so
*/
void Starfield::add_star( int x, int y )
{
    /*  Create an instance of the star struct */
    Star star;

    /*  Assign position according to given coordinates */
    star.pos.x = x;
    star.pos.y = y;

    /*
     *  There is a 1/4 chance of the star being one of eight of the default
     *  colors available (including white as a possibility)
     */
    if( rand() % 4 == 0 )
        star.color = colors[ ( (rand()%8) + 1 ) ];

    /*  Otherwise, it's just white */
    else
        star.color = colors[ COLOR_WHITE ];

    /*  1/10 chance that the star will twinkle */
    rand() % 10 == 0 ? star.twinkle = true : star.twinkle = false;

    /*
     *  We set the minimum alpha of all stars from 64 - 191.  This isn't really
     *  used unless the star twinkles, though.
     */
    star.alphaMin = ( rand() % 127 ) + 64;

    /*  Push the star onto the stars vector */
    mStars.push_back( star );
}


/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Starfield::update( void )
{
    /*  Erase dead stars */
    for( mStar = mStars.begin(); mStar != mStars.end(); )
    {
        /*  Kill the star */
        if( mStar->pos.y > BHEIGHT )
            mStars.erase( mStar );
        
        /*  Or don't */
        else
            ++mStar;
    }


    /*  Move active stars */
    for( mStar = mStars.begin(); mStar != mStars.end(); ++mStar )
    {
        /*  Move downward */
        mStar->pos.y += warpSpeed;

        /*  Modify star alpha value */
        if( mStar->twinkle )
        {
            /*  If alpha has gone below minimum threshold, reset it */
            if( mStar->color.a < mStar->alphaMin )
                mStar->color.a = 255;

            /*  Otherwise, just decrement star alpha value */
            else
                --mStar->color.a;
        }
    }

    /*  Create new stars */
    for( int col = 0; col < BWIDTH; ++col )
    {
        /*
         *  Every 'tick', approx. 1 in 1000 chance of a new star being added to
         *  the top-most row of the pixels on the screen
         */
        if( rand() % ( 1000 / warpSpeed ) == 0 )
        {
            add_star( col, 0 );
        }
    }

}


/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  The render functions.  The main one just tells the program which actual
 *  rendering function to call.  render_normal() renders the stars during
 *  regular gameplay, whereas render_warp() renders the stars while the player
 *  is 'powered' and moving faster
*/
void Starfield::render_normal( void )
{
    for( mStar = mStars.begin(); mStar != mStars.end(); ++mStar )
    {
        /*  Set the render draw color */
        SDL_SetRenderDrawColor( gRenderer, mStar->color.r, mStar->color.g,
                mStar->color.b, mStar->color.a );

        /*  Draw the point */
        SDL_RenderDrawPoint( gRenderer, mStar->pos.x, mStar->pos.y );
    }
}

void Starfield::render_warp( void )
{
    for( mStar = mStars.begin(); mStar != mStars.end(); ++mStar )
    {
        /*  Set the render draw color */
        SDL_SetRenderDrawColor( gRenderer, mStar->color.r, mStar->color.g,
                mStar->color.b, 127 - ( warpSpeed * 3 ) );

        /*  Draw the lines */
        SDL_RenderDrawLine( gRenderer,
                mStar->pos.x, mStar->pos.y,
                mStar->pos.x, mStar->pos.y - ( warpSpeed * 4 ) );
    }
}

void Starfield::render( void )
{
    if( warpSpeed > 1 )
        render_warp();
    else
        render_normal();
}
