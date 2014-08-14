/*******************************************************************************
 *  collision.cpp
 *
 *  This file defines the functions used to check for collisions.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                DISTANCE SQUARED
--------------------------------------------------------------------------------
 *  Returns the distance between two points squared.  We do this because the
 *  alternative is to get the square root, which is more computationally
 *  expensive.
*/
double distance_squared( int x1, int y1, int x2, int y2 )
{
    /*  Get the distance */
    int diffX = x2 - x1;
    int diffY = y2 - y1;

    /*  Return the distance squared */
    return( (diffX * diffX) + (diffY * diffY) );
}



/*
--------------------------------------------------------------------------------
                                COLLISION CIRCLE
--------------------------------------------------------------------------------
 *  Checks for collisions between two circles
*/
bool check_collision_circ( Circle &a, Circle &b )
{
    /*  Total radius squared */
    int trs = (a.r + b.r) * (a.r + b.r );

    //  If the difference between centers is less than the total radius squared
    if( distance_squared( a.x, a.y, b.x, b.y ) < trs )
        return( true );

    /*  Otherwise, no collision */
    return( false );
}



/*
--------------------------------------------------------------------------------
                                 COLLISION BOX
--------------------------------------------------------------------------------
 *  Checks for collisions between two rectangles.  This is the 'separating axis'
 *  test.
*/
bool check_collision_box( SDL_Rect &rectA, SDL_Rect &rectB )
{
    /*  Create sides for player rectangle */
    int leftA = rectA.x;
    int rightA = rectA.x + rectA.w;
    int topA = rectA.y;
    int bottomA = rectA.y + rectA.h;

    /*  Create sides for enemy rectangle */
    int leftB = rectB.x;
    int rightB = rectB.x + rectB.w;
    int topB = rectB.y;
    int bottomB = rectB.y + rectB.h;

    /*  If any of these are true, return false (no collision) */
    if( rightA <= leftB )
        return( false );
    if( leftA >= rightB )
        return( false );
    if( bottomA <= topB )
        return( false );
    if( topA >= bottomB )
        return( false );

    /*  If none of those were true, we have a collision */
    return( true );
}



/*
--------------------------------------------------------------------------------
                              COLLISION COLLIDERS
--------------------------------------------------------------------------------
 *  Check for collisions between two vectors of colliders.  This is used for
 *  per-pixel collision detection.
*/
bool check_collision_colliders( std::vector<Collider> &collidersA,
        std::vector<Collider> &collidersB )
{
    /*  These rects will be used for each opposing collider rect */
    SDL_Rect aRect, bRect;


    /*  Loop for the first set of colliders */
    for( unsigned int a = 0; a < collidersA.size(); ++a )
    {
        /*
         *  We skip back to the top of the loop if there's nothing in this part
         *  of the collider to collide with
         */
        if( collidersA[ a ].w < 1 )
            continue;

        /*  Fill in the rect for the player */
        aRect.x = collidersA[ a ].x;
        aRect.y = collidersA[ a ].y;
        aRect.w = collidersA[ a ].w;
        aRect.h = collidersA[ a ].h;


        /*  Loop for the second set of colliders */
        for( unsigned int b = 0; b < collidersB.size(); ++b )
        {
            /*  If nothing to collide with, skip back to the top of the loop */
            if( collidersB[ b ].w < 1 )
                continue;

            /*  Fill in the rect for the enemy */
            bRect.x = collidersB[ b ].x;
            bRect.y = collidersB[ b ].y;
            bRect.w = collidersB[ b ].w;
            bRect.h = collidersB[ b ].h;

            /*  Check collision */
            if( check_collision_box( aRect, bRect ) )
                return( true );
        }
    }

    /*  If no collider collision was detected */
    return( false );
}



/*
--------------------------------------------------------------------------------
                            COLLISION RECT : CIRCLE
--------------------------------------------------------------------------------
 *  This function checks for collisions between rectangles and circles
*/
bool check_collision_rect_circ( SDL_Rect &rect, Circle &circ )
{
    /*  Closest position */
    SDL_Point c;

    /*  Find closest X position */
    c.x = circ.x;
    if( circ.x < rect.x )
        c.x = rect.x;
    else if( circ.x > rect.x + rect.w )
        c.x = rect.x + rect.w;

    /*  Closest Y position */
    c.y = circ.y;
    if( circ.y < rect.y )
        c.y = rect.y;
    else if( circ.y > rect.y + rect.h )
        c.y = rect.y + rect.h;

    /*  If the closest point is inside of our circle */
    if( distance_squared( circ.x, circ.y, c.x, c.y ) < (circ.r * circ.r))
        return( true );     //  Collision

    /*  Otherwise, no collision */
    return( false );
}
