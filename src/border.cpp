/*******************************************************************************
 *  border.cpp
 *
 *  This file defines the draw_border function, which draws a border around the
 *  play boundaries of the screen while the player is powered.  The border
 *  shifts color to match that of the player's car.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  DRAW BORDER
--------------------------------------------------------------------------------
 *  Draw the border, man.  Draw it.
*/
void draw_border( void )
{
    /*  Set the color */
    SDL_Color *c = player.get_special_color();
    SDL_SetRenderDrawColor( gRenderer, c->r, c->g, c->b, c->a );

    /*  Init rect */
    SDL_Rect rect;

    /*  Top border */
    rect.x = rect.y = 0;
    rect.w = BWIDTH;
    rect.h = 4;
    SDL_RenderFillRect( gRenderer, &rect );

    /*  Bottom border */
    rect.y = BHEIGHT - rect.h;
    SDL_RenderFillRect( gRenderer, &rect );

    /*  Left border */
    rect.y = 0;
    rect.h = BHEIGHT;
    rect.w = 4;
    SDL_RenderFillRect( gRenderer, &rect );

    /*  Right border */
    rect.x = BWIDTH - rect.w;
    SDL_RenderFillRect( gRenderer, &rect );
}
