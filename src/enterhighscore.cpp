/*******************************************************************************
 *  enterhighscore.cpp
 *
 *  Defines the 'enter high score' screen
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                             INIT HIGH SCORE SCREEN
--------------------------------------------------------------------------------
 *  Creates textures, sets texture positions, and sets other key attributes
*/
bool init_high_score_screen( void )
{
    /*  Create the texture objects */
    enterHighScoreText1 = new Texture();
    enterHighScoreText2 = new Texture();

    /*  Load the texture for the new high score text */
    if( ! enterHighScoreText1->create_texture_from_string( gFontSmall,
                "NEW HIGH SCORE", colors[ COLOR_WHITE ] ) )
        return( false );

    /*  Load the texture for the score itself */
    char scoreStr[ 16 ];
    snprintf( scoreStr, 16, "%06u", currentScore );
    if( ! enterHighScoreText2->create_texture_from_string( gFont, scoreStr,
                colors[ COLOR_WHITE ] ) )
        return( false );


    /*  Sets the positions of the 'initials' texture objects */
    for( int i = 0; i < 3; ++i )
    {
        initials[ i ]->get_texture_object()->set_position(
                (( BWIDTH - ( (initials[ i ]->get_texture_object()->
                               get_width() * 3) + 100) ) / 2 ) + i * 100, 300 );
    }

    /*  This is the score itself, rendered above the flashing 'new score' str */
    enterHighScoreText2->set_position(
            ( BWIDTH - enterHighScoreText2->get_width() ) / 2,
            initials[ 0 ]->get_texture_object()->get_pos_y() + 200 );

    /*  This position is set relative to the score texture above */
    enterHighScoreText1->set_position(
            ( BWIDTH - enterHighScoreText1->get_width() ) / 2,
            enterHighScoreText2->get_pos_y() + 40 );


    /*  Reset current focus value */
    int currentFocus = 0;

    /*  Set flash stuff */
    for( int i = 0; i < 3; ++i )
    {
        initials[ i ]->set_max_flash_ticks(
                initials[ i ]->get_max_flash_ticks_default() / 4 );

        if( initials[ i ]->has_focus() )
            currentFocus = i;
    }

    /*  Set the focus to whatever had the focus.  If nothing, it's at zero. */
    initials[ currentFocus ]->set_focus( true );

    return( true );
}



/*
--------------------------------------------------------------------------------
                                ENTER HIGH SCORE
--------------------------------------------------------------------------------
 *  Master function called when the player is allowed to enter their high score
*/
void enter_high_score( void )
{
    /*  Call the initialization function defined above */
    if( ! init_high_score_screen() )
    {
        printf("ERROR:  Could not init high score screen\n");
        quit = true;
    }

    /*  Set the 'new' flag on the scores screen */
    gScores->set_new( true );

    /*  Do transition */
    start_transition( SCREEN_ENTER_HIGH_SCORE, DIRECTION_UP );
}
