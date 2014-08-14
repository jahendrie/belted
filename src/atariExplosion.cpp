/*******************************************************************************
 *  atariExplosion.cpp
 *
 *  This file defines the atariExplosion class, used to create colorful, blocky
 *  explosions when the player runs into enemies while powered up.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
 *  Create the object
*/
AtariExplosion::AtariExplosion( void )
{
    mColor = NULL;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
 *  Free memory, null stuff
*/
AtariExplosion::~AtariExplosion( void )
{
    mExplosionRects.clear();
    mColor = NULL;
}


/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Do the actual class initialzation
*/
void AtariExplosion::init( int x, int y, SDL_Color *color )
{
    /*  Init the color */
    mColor = color;

    /*  Used for random left/right up/down choices */
    int choices[] = { -1, 1 };

    /*  Create at least twenty squares for the explosion */
    for( int i = 0; i < ( (rand()%100) + 20 ); ++i )
    {
        /*  Create this to store position / dimensions */
        ARect arect;

        /*  Set current position */
        arect.pos.x = x;
        arect.pos.y = y;

        /*  Set target position */
        arect.target.x = x + ( (( rand()%50 ) + 20) * choices[ rand()%2 ] );
        arect.target.y = y + ( (( rand()%50 ) + 20) * choices[ rand()%2 ] );

        /*  Init velocity */
        arect.velocity.x = ( rand() % 10 ) + 5;
        arect.velocity.y = ( rand() % 10 ) + 5;

        /*  Random width, random height */
        arect.w = ( rand() % 200 ) + 50;
        arect.h = ( rand() % 60 ) + 20;

        /*  Init the alpha value to full */
        arect.a = 255;

        /*  This rect has just begin */
        arect.done = false;

        /*  Push the finished ARect onto the ARects vector */
        mExplosionRects.push_back( arect );
    }
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  Render all of the explosion rects
*/
void AtariExplosion::render( void )
{
    /*  The draw rect, which will be set to that of each explosion rect */
    SDL_Rect dRect;

    /*  Iterate along the explosion rects vector */
    std::vector<ARect>::iterator r;
    for( r = mExplosionRects.begin(); r != mExplosionRects.end(); ++r )
    {
        /*  Set the draw rect to the position / dimensions of the expl. rect */
        dRect.x = r->pos.x;
        dRect.y = r->pos.y;
        dRect.w = r->w;
        dRect.h = r->h;

        /*  Set the render draw color to the values we need */
        SDL_SetRenderDrawColor( gRenderer,
                mColor->r, mColor->g, mColor->b, r->a );

        /*  Draw the rectangle onto the screen */
        SDL_RenderFillRect( gRenderer, &dRect );
    }
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Update all of the explosion rects
*/
void AtariExplosion::update( SDL_Color *color )
{
    /*  If the color isn't null, we change the mColor var to match it */
    if( color != NULL )
        mColor = color;

    /*  Create the iterator for the explosions rect vector */
    std::vector<ARect>::iterator r;

    /*  First, get rid of all the dead rects */
    for( r = mExplosionRects.begin(); r != mExplosionRects.end(); )
    {
        /*  If the rect is done, erase it from the vector */
        if( r->done )
            mExplosionRects.erase( r );

        /*  Otherwise, keep on moving */
        else
            ++r;
    }

    /*  Next, iterate along the explosion rects vector and update the rects */
    for( r = mExplosionRects.begin(); r != mExplosionRects.end(); ++r )
    {
        /*  Move along the X axis */
        if( r->pos.x < r->target.x )
            r->pos.x += r->velocity.x;
        else if( r->pos.x > r->target.x )
            r->pos.x -= r->velocity.x;

        /*  Move along the Y axis */
        if( r->pos.y < r->target.y )
            r->pos.y += r->velocity.y;
        else if( r->pos.y > r->target.y )
            r->pos.y -= r->velocity.y;

        /*  Adjust alpha value (fade out) */
        if( r->a >= 32 )
            r->a -= 32;
        else
            r->done = true;

    }
}



/*
--------------------------------------------------------------------------------
                                    IS DONE
--------------------------------------------------------------------------------
 *  Returns whether or not the vector is entirely clear of explosion rects
*/
bool AtariExplosion::is_done( void )
{
    return( mExplosionRects.size() == 0 );
}
