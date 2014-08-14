/*******************************************************************************
 *  gameover.cpp
 *
 *  This file defines functions to initialize the game over screen and pass the
 *  transition on to the start_transition() function.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                            INIT GAME OVER TEXTURES
--------------------------------------------------------------------------------
 *  Create, load and position the game over screen textures
*/
bool init_game_over_textures( void )
{
    /*  Use these for the qualify text strings */
    std::string qStr1, qStr2, qStr3;

    /*  Create the textures objects */
    scoreQualifyText1 = new Texture();
    scoreQualifyText2 = new Texture();
    scoreQualifyText3 = new Texture();

    /*  Create a couple of SDL_Colors which will be defined momentarily */
    SDL_Color sqColor1, sqColor3;

    /*
     *  qStr2 is the middle string, which always informs the player of his or
     *  her option to return to play without entering a score or viewing the
     *  scores.
     */
    qStr2 = "Right click to return to play";

    /*  If their score qualifies, set the strings accordingly */
    if( gScores->score_qualifies( currentScore ) )
    {
        /*  Assign the strings */
        qStr1 = "SCORE QUALIFIES";
        qStr3 = "Left click to enter score into hall of fame";

        /*  Make this texture flashy */
        scoreQualifyText1->set_flashing( true );

        /*  Assign the texture colors */
        sqColor1 = colors[ COLOR_WHITE ];
        sqColor3 = colors[ COLOR_GREEN ];
    }

    /*  Otherwise, set the strings to reflect FAILURE */
    else
    {
        /*  Set strings */
        qStr1 = "Score does not qualify";
        qStr3 = "Left click to view high scores";

        /*  Set the first qualify text color (salmon, for FAILURE) */
        sqColor1.r = sqColor1.a = 255;
        sqColor1.g = sqColor1.b = 64;

        /*  Set color for the final string texture */
        sqColor3 = colors[ COLOR_WHITE ];
    }


    /*
     *  Generate the textures
     */
    if( ! scoreQualifyText1->create_texture_from_string( gFontSmall,
                qStr1.c_str(), sqColor1 ) )
        return( false );

    if( ! scoreQualifyText2->create_texture_from_string( gFontTiny,
                qStr2.c_str(), colors[ COLOR_WHITE ] ) )
        return( false );

    if( ! scoreQualifyText3->create_texture_from_string( gFontTiny,
                qStr3.c_str(), sqColor3 ) )
        return( false );



    /*  Lay out the main game over text */
    gameOverText->set_position(
            ( BWIDTH - gameOverText->get_width() ) / 2,
            ( BHEIGHT - gameOverText->get_width() ) / 2 );

    /*  Lay out the qualify text textures */
    scoreQualifyText1->set_position(
            ( BWIDTH - scoreQualifyText1->get_width() ) / 2,
            gameOverText->get_pos_y() + 100 );

    /*  Position the 'right click to blah blah blah' texture */
    scoreQualifyText2->set_position(
            ( BWIDTH - scoreQualifyText2->get_width() ) / 2,
            scoreQualifyText1->get_pos_y() + 40 );

    /*  Position the third, 'left click' texture */
    scoreQualifyText3->set_position(
            ( BWIDTH - scoreQualifyText3->get_width() ) / 2 ,
            scoreQualifyText1->get_pos_y() + 70 );


    /*  If all is good, return true */
    return( true );
}


/*
--------------------------------------------------------------------------------
                                   GAME OVER
--------------------------------------------------------------------------------
 *  This is the main function called when the game over first happens
*/
void game_over( void )
{
    /*  Init all of the things */
    if( ! init_game_over_textures() )
    {
        printf("ERROR:  Could not init game over screen\n");
    }

    /*  If the music is playing, halt it */
    if( Mix_PlayingMusic() == 1 )
        Mix_HaltMusic();

    /*  Disable the screen flash */
    screenFlash = false;

    /*  Do the transition */
    start_transition( SCREEN_GAME_OVER, DIRECTION_UP );
}
