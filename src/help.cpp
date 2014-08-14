/*******************************************************************************
 *  help.cpp
 *
 *  This file defines the help class (help screen).  It initializes the help
 *  screen, in addition to creating, loading, positioning and rendering the
 *  textures for the help screen.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
 *  This gets called when the help screen object is created
*/
Help::Help( void )
{
    /*  Null all the textures */
    for( int i = 0; i < TOTAL_HELP_SCREEN_TEXTURES; ++i )
    {
        mHelpTextures[ i ] = NULL;
    }

    /*  Border stuff */
    borderColor = colors[ COLOR_WHITE ];
    borderPulse = -1;
}



/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
 *  Called when the help screen object is deleted
*/
Help::~Help( void )
{
    /*  Free the textures */
    free_textures();
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Master function for help screen initialization
*/
bool Help::init( void )
{
    /*  Free textures if they exist */
    free_textures();

    /*  Create the textures anew */
    if( ! create_textures() )
    {
        printf("ERROR:  Could not create help screen textures\n");
        return( false );
    }

    /*  Lay all the textures out */
    this->layout();

    return( true );
}



/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
 *  Does exactly what it says on the tin
*/
void Help::free_textures( void )
{
    /*
     *  Go through the help screen textures array, finding any that aren't
     *  null and then deleting those and nulling out their pointers.
     */
    for( int i = 0; i < TOTAL_HELP_SCREEN_TEXTURES; ++i )
    {
        /*  If it isn't null, TERMINATE */
        if( mHelpTextures[ i ] != NULL )
        {
            delete mHelpTextures[ i ];
            mHelpTextures[ i ] = NULL;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                CREATE TEXTURES
--------------------------------------------------------------------------------
 *  Create and load texture objects
*/
bool Help::create_textures( void )
{
    /*  Create all of the texture objects */
    for( int i = 0; i < TOTAL_HELP_SCREEN_TEXTURES; ++i )
    {
        mHelpTextures[ i ] = new Texture();
    }

    /*  Load the title text */
    if( ! mHelpTextures[ H_TITLE ]->create_texture_from_string( gFont,
                "GAME INFO", colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create help screen title texture\n");
        return( false );
    }

    /*  Honk text */
    if( ! mHelpTextures[ H_HONK1 ]->create_texture_from_string( gFontSmall,
                "to honk:", colors[ COLOR_WHITE ] ))
    {
        printf("ERROR:  Could not create help screen honk texture\n");
        return( false );
    }

    if( ! mHelpTextures[ H_HONK2 ]->create_texture_from_string( gFontTiny,
                "press space or left click", colors[ COLOR_WHITE ] ))
    {
        printf("ERROR:  Could not create help screen honk texture\n");
        return( false );
    }

    /*  Power text */
    if( ! mHelpTextures[ H_POWER1 ]->create_texture_from_string( gFontSmall,
                "to activate power:",
                colors[ COLOR_WHITE ] ))
    {
        printf("ERROR:  Could not create help screen honk texture\n");
        return( false );
    }

    if( ! mHelpTextures[ H_POWER2 ]->create_texture_from_string( gFontTiny,
                "press shift or right click",
                colors[ COLOR_WHITE ] ))
    {
        printf("ERROR:  Could not create help screen honk texture\n");
        return( false );
    }


    /*  Mouse text */
    if( ! mHelpTextures[ H_MOUSE ]->create_texture_from_string( gFontTiny,
                "best played with a mouse",
                colors[ COLOR_ORANGE ] ) )
    {
        printf("ERROR:  Could not create help mouse text texture\n");
        return( false );
    }


    /*  Help screen screenshot graphic */
    if( ! mHelpTextures[ H_SS ]->create_texture_from_file(
                "data/gfx/screenshot.png" ) )
    {
        printf("ERROR:  Could not create help screen screenshot texture\n");
        return( false );
    }


    /*  If we made it this far, good */
    return( true );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
 *  This function positions all of the textures
*/
void Help::layout( void )
{
    /*  Set title position */
    mHelpTextures[ H_TITLE ]->set_position(
            ( BWIDTH - mHelpTextures[ H_TITLE ]->get_width() ) / 2, 60 );

    /*  Position screen shot */
    mHelpTextures[ H_SS ]->set_position(
            ( BWIDTH - mHelpTextures[ H_SS ]->get_width() ) / 2, 100 );

    /*  This is solely for my own convenience */
    int y = ( mHelpTextures[ H_SS ]->get_pos_y() +
            mHelpTextures[ H_SS ]->get_height() );

    /*  Position honk text */
    mHelpTextures[ H_HONK1 ]->set_position(
            ( BWIDTH - mHelpTextures[ H_HONK1 ]->get_width() ) / 2, y + 70 );
    mHelpTextures[ H_HONK2 ]->set_position(
            ( BWIDTH - mHelpTextures[ H_HONK2 ]->get_width() ) / 2, y + 100 );

    /*  Position power text */
    mHelpTextures[ H_POWER1 ]->set_position(
            ( BWIDTH - mHelpTextures[ H_POWER1 ]->get_width() ) / 2, y + 170 );
    mHelpTextures[ H_POWER2 ]->set_position(
            ( BWIDTH - mHelpTextures[ H_POWER2 ]->get_width() ) / 2, y + 200 );

    /*  Position mouse text */
    mHelpTextures[ H_MOUSE ]->set_position(
            ( BWIDTH - mHelpTextures[ H_MOUSE ]->get_width() ) / 2, y + 272 );

}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  GUESS WHAT THIS FUNCTION DOES
*/
void Help::render( void )
{
    /*  Render all the textures */
    for( int i = 0; i < TOTAL_HELP_SCREEN_TEXTURES; ++i )
    {
        mHelpTextures[ i ]->render_self();
    }

    /*  Draw a border around the screenshot */
    adjust_border();
    render_texture_border( mHelpTextures[ H_SS ] );
}
