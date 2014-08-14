/*******************************************************************************
 *  render.cpp
 *
 *  This file defines the functions used to render everything in the game.  It
 *  either renders everything directly or it calls the rendering functions of
 *  various class instances.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  RENDER MAIN
--------------------------------------------------------------------------------
 *  This function renders everything on the main screen during play.
*/
void render_main( void )
{
    /*  Render the starfield */
    starfield->render();

    /*  Render the tail */
    if( tail.is_active() || tail.is_fading() )
        tail.render();

    /*  Render the player's ship */
    player.render();

    /*  Render the enemies */
    if( enemies.size() > 0 )
    {
        /*  Create the enemy iterator */
        std::vector<Enemy>::iterator enemy;

        /*  Iterate through the enemies vector */
        for( enemy = enemies.begin(); enemy != enemies.end(); ++enemy )
        {
            /*  If they're alive, render them */
            if( enemy->is_alive() )
                enemy->render();

            //  Otherwise, they must have been killed, so render the explosion
            else if( enemy->is_exploding() )
                enemy->render_exploding();
        }
    }

    /*  If the screen is flashing, render it */
    if( screenFlash )
    {
        /*  The flash is drawn over the entire play area */
        SDL_Rect rect = { 0, 0, BWIDTH, BHEIGHT };

        /*  Colored white */
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );

        /*  Render it */
        SDL_RenderFillRect( gRenderer, &rect );

        /*  Set it to false after rendering once */
        screenFlash = false;
    }

    /*  Render the 'atari' explosions */
    std::vector<AtariExplosion>::iterator a;
    for( a = aExplosions.begin(); a != aExplosions.end(); ++a )
        a->render();

    /*  Render the panel */
    panel.render();

    /*  Render kiss/kill text OSDs */
    kissKills.render();

    /*
     *  If the player is in 'special' mode, render a color border around the
     *  screen
     */
    if( player.is_powered() )
        draw_border();

    /*  If the OSD exists, render it */
    render_osd();
}


/*
--------------------------------------------------------------------------------
                                  RENDER PULSE
--------------------------------------------------------------------------------
 *  This function renders one texture pulsing over the other at a given speed
*/
void render_pulse( Texture *textureMain, Texture *texturePulse, int speed )
{
    /*  Get and modify the alpha value of the white texture */
    int alpha = texturePulse->get_alpha();

    /*  If we're pulsing 'backward' (becoming more transparent) */
    if( pulseDirection < 0 )
    {
        /*  If the alpha is zero, flip the pulse direction */
        if( alpha == 0 )
            pulseDirection *= -1;

        /*  Otherwise, decrease alpha by the given 'speed' variable */
        else
            alpha -= speed;
    }


    /*  If we're pulsing forward (becoming more opaque) */
    else if( pulseDirection > 0 )
    {
        /*  If we've reached full opacity, flip the pulse direction */
        if( alpha == 255 )
            pulseDirection *= -1;

        /*  Otherwise, increase alpha by speed */
        else
            alpha += speed;
    }

    /*  Correct the alpha value */
    if( alpha > 255 )
        alpha = 255;
    else if( alpha < 0 )
        alpha = 0;

    /*  Assign alpha value to the overlay pulse texture */
    texturePulse->set_alpha( alpha );

    //  Render both textures, first the normal one and then the overlay atop it
    textureMain->render_self();
    texturePulse->render_self();
}



/*
--------------------------------------------------------------------------------
                                 ADJUST BORDER
--------------------------------------------------------------------------------
 *  This function adjusts the global borderColor variable, as well as the
 *  pulse direction variable.  It's called by help.cpp, though I put it here in
 *  case I want to use it in some future function.
*/
void adjust_border( void )
{
    /*  Get initial value */
    int a = borderColor.a;

    /*  Adjust alpha / colors down */
    if( pulseDirection < 0 )
    {
        a -= 2;

        if( a <= 0 )
        {
            a = 0;
            pulseDirection *= -1;
        }
    }

    /*  Adjust alpha / colors up */
    else if( pulseDirection > 0 )
    {
        a += 2;

        if( a >= 255 )
        {
            a = 255;
            pulseDirection *= -1;
        }
    }

    /*  Reset border color */
    borderColor.a = a;
}


/*
--------------------------------------------------------------------------------
                                 RENDER BORDER
--------------------------------------------------------------------------------
 *  This draws a rectangular border according to a series of four points.  In
 *  order, these points are the top-left, top-right, bottom-right and
 *  bottom-left.
*/
void render_border( SDL_Point tl, SDL_Point tr, SDL_Point br, SDL_Point bl )
{
    /*  Set the render draw color */
    SDL_SetRenderDrawColor( gRenderer,
            borderColor.r,
            borderColor.g,
            borderColor.b,
            borderColor.a );

    /*
     *  Draw the lines
     */

    /*  Top */
    SDL_RenderDrawLine( gRenderer, tl.x, tl.y, tr.x, tr.y );

    /*  Right side */
    SDL_RenderDrawLine( gRenderer, tr.x, tr.y, br.x, br.y );

    /*  Bottom */
    SDL_RenderDrawLine( gRenderer, br.x, br.y, bl.x, bl.y );

    /*  Left side */
    SDL_RenderDrawLine( gRenderer, bl.x, bl.y, tl.x, tl.y );
}



/*
--------------------------------------------------------------------------------
                             RENDER TEXTURE BORDER
--------------------------------------------------------------------------------
 *  This function gets the points needed to draw a border from a given texture,
 *  then calls the draw_border() function to draw a border around the given
 *  texture.
*/
void render_texture_border( Texture *texture )
{
    /*
     *  Get the points for drawing
     */

    /*  The points */
    SDL_Point p[ 4 ];

    /*  Top left */
    p[ 0 ].x = texture->get_pos_x();
    p[ 0 ].y = texture->get_pos_y();

    /*  Top right */
    p[ 1 ].x = p[0].x + texture->get_width();
    p[ 1 ].y = p[0].y;

    /*  Bottom right */
    p[ 2 ].x = p[1].x;
    p[ 2 ].y = p[0].y + texture->get_height();

    /*  Bottom left */
    p[ 3 ].x = p[0].x;
    p[ 3 ].y = p[2].y;

    /*  Render the lines */
    render_border( p[0], p[1], p[2], p[3] );

}



/*
--------------------------------------------------------------------------------
                                  RENDER MENU
--------------------------------------------------------------------------------
 *  This calls the menuScreen object's render function to render, what else,
 *  the main menu screen.
*/
void render_menu( void )
{
    menuScreen->render();
}



/*
--------------------------------------------------------------------------------
                                RENDER GAME OVER
--------------------------------------------------------------------------------
 *  This function renders the game over screen.
*/
void render_game_over( void )
{
    /*  Render main game over text texture */
    gameOverText->render_self();

    /*  Render top score qualify text */
    if( scoreQualifyText1->is_flashing() )
        scoreQualifyText1->render_flashing();
    else
        scoreQualifyText1->render_self();

    /*  Render the second and third ones */
    scoreQualifyText2->render_self();
    scoreQualifyText3->render_self();
}



/*
--------------------------------------------------------------------------------
                               RENDER HIGH SCORES
--------------------------------------------------------------------------------
 *  This function calls the high scores screen's render function.
*/
void render_high_scores( void )
{
    gScores->render();
}



/*
--------------------------------------------------------------------------------
                                 RENDER CREDITS
--------------------------------------------------------------------------------
 *  This function calls the credits screen render function.
*/
void render_credits( void )
{
    credits->render();
}



/*
--------------------------------------------------------------------------------
                                  RENDER HELP
--------------------------------------------------------------------------------
 *  This function calls the help screen render function.
*/
void render_help( void )
{
    helpScreen->render();
}



/*
--------------------------------------------------------------------------------
                            RENDER ENTER HIGH SCORE
--------------------------------------------------------------------------------
 *  This function renders the 'enter high score' screen
*/
void render_enter_high_score( void )
{
    /*  Render each initial properly */
    for( int i = 0; i < 3; ++i )
    {
        if( initials[ i ]->is_flashing() )
            initials[ i ]->get_texture_object()->render_flashing();
        else
            initials[ i ]->get_texture_object()->render_self();
    }

    /*  New high score text */
    if( enterHighScoreText1->is_flashing() )
        enterHighScoreText1->render_flashing();
    else
        enterHighScoreText1->render_self();

    /*  The score itself */
    enterHighScoreText2->render_self();
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  This is the master render function, calling the other appropriate render
 *  functions according to which screen the player is currently on.
*/
void render( void )
{
    if( currentScreen == SCREEN_MAIN )
        render_main();

    else if( currentScreen == SCREEN_MENU )
        render_menu();

    else if( currentScreen == SCREEN_GAME_OVER )
        render_game_over();

    else if( currentScreen == SCREEN_HIGH_SCORES )
        render_high_scores();

    else if( currentScreen == SCREEN_TRANSITION )
        render_transition();

    else if( currentScreen == SCREEN_ENTER_HIGH_SCORE )
        render_enter_high_score();

    else if( currentScreen == SCREEN_HELP )
        render_help();

    else if( currentScreen == SCREEN_CREDITS )
        render_credits();
}
