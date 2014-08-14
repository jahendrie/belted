/*******************************************************************************
 *  credits.cpp
 *
 *  This file defines the credits class.  Essentially, it initializes, lays out
 *  and renders the credits screen.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
*   Set everything to NULL to begin with
*/
Credits::Credits( void )
{
    /*  Null the textures */
    mAuthor = NULL;
    mAuthorNameYellow = NULL;
    mAuthorNameWhite = NULL;
    mAuthorEmail = NULL;
    mAuthorWebsite = NULL;
    mMusic1 = NULL;
    mMusic2 = NULL;
    mCredits = NULL;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
 *  Calls the function to free the memory
*/
Credits::~Credits( void )
{
    /*  Free the textures */
    free_textures();
}



/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
 *  This function does the actual memory freeing
*/
void Credits::free_textures( void )
{
    /*  Author picture texture */
    if( mAuthor != NULL )
    {
        delete mAuthor;
        mAuthor = NULL;
    }

    /*  Author name texture (normal, 'yellow' version) */
    if( mAuthorNameYellow != NULL )
    {
        delete mAuthorNameYellow;
        mAuthorNameYellow = NULL;
    }

    /*  Author name texture (the layover 'white' texture */
    if( mAuthorNameWhite != NULL )
    {
        delete mAuthorNameWhite;
        mAuthorNameWhite = NULL;
    }

    /*  Author email texture */
    if( mAuthorEmail != NULL )
    {
        delete mAuthorEmail;
        mAuthorEmail = NULL;
    }

    /*  Author website texture */
    if( mAuthorWebsite != NULL )
    {
        delete mAuthorWebsite;
        mAuthorWebsite = NULL;
    }

    /*  First line of brief music credits */
    if( mMusic1 != NULL )
    {
        delete mMusic1;
        mMusic1 = NULL;
    }

    /*  Second line of brief music credits */
    if( mMusic2 != NULL )
    {
        delete mMusic2;
        mMusic2 = NULL;
    }

    /*  Line that says 'see credits.txt for more' */
    if( mCredits != NULL )
    {
        delete mCredits;
        mCredits = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  This function creates and loads all of the textures
*/
bool Credits::init( void )
{
    /*  Free textures if they exist */
    free_textures();

    /*  Load author photograph */
    mAuthor = new Texture();
    if( ! mAuthor->create_texture_from_file( "data/gfx/author.png" ) )
    {
        printf("ERROR:  Could not load author's handsome photograph!\n" );
        return( false );
    }


    /*  Load author name texture */
    mAuthorNameYellow = new Texture();
    if( ! mAuthorNameYellow->create_texture_from_string( gFont, "James Hendrie",
                colors[ COLOR_YELLOW ] ) )
    {
        printf("ERROR:  Could not create author's name\n");
        return( false );
    }

    /*  Load the second, layover white texture for the author's name */
    mAuthorNameWhite = new Texture();
    if( ! mAuthorNameWhite->create_texture_from_string( gFont, "James Hendrie",
                colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create author's name\n");
        return( false );
    }

    /*  Start the second texture with an alpha of zero (fully transparent) */
    mAuthorNameWhite->set_alpha( 0 );


    /*  Email texture */
    SDL_Color emailColor = { 127, 127, 0, 255 };
    mAuthorEmail = new Texture();
    if( ! mAuthorEmail->create_texture_from_string( gFontTiny,
                "hendrie.james@gmail.com", emailColor ) )
    {
        printf("ERROR:  Could not create author email texture\n");
        return( false );
    }

    /*  Website texture */
    SDL_Color websiteColor = { 64, 64, 0, 255 };
    mAuthorWebsite = new Texture();
    if( ! mAuthorWebsite->create_texture_from_string( gFontTiny,
                "someplacedumb.net/games", websiteColor ) )
    {
        printf("ERROR:  Could not create author website texture\n");
        return( false );
    }

    /*  First line of music credits */
    SDL_Color musicColor1 = colors[ COLOR_CYAN ];
    mMusic1 = new Texture();
    if( ! mMusic1->create_texture_from_string( gFontSmall,
                "Music by Kevin MacLeod", musicColor1 ) )
    {
        printf("ERROR:  Could not create music author's name texture\n");
        return( false );
    }

    /*  Second line of music credits */
    SDL_Color musicColor2 = { 0, 127, 127, 255 };
    mMusic2 = new Texture();
    if( ! mMusic2->create_texture_from_string( gFontTiny,
                "incompetech.com", musicColor2 ) )
    {
        printf("ERROR:  Could not create music author's website texture\n");
        return( false );
    }

    /*  Line that says 'see credits.txt for more' */
    mCredits = new Texture();
    if( ! mCredits->create_texture_from_string( gFontTiny,
                "SEE CREDITS.TXT FOR MORE INFO", colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create credits.txt text texture\n");
        return( false );
    }

    /*  Position textures */
    this->layout();

    /*  If we're good */
    return( true );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
 *  This function positions all of the credits textures
*/
void Credits::layout( void )
{
    /*  Position author photograph */
    mAuthor->set_position(
            ( BWIDTH - mAuthor->get_width() ) / 2, 20 );

    int y = mAuthor->get_pos_y() + mAuthor->get_height() + 20;

    /*  Position author name text texture (yellow) */
    mAuthorNameYellow->set_position(
            ( BWIDTH - mAuthorNameYellow->get_width() ) / 2, y );

    /*  Position author name text texture (white) */
    mAuthorNameWhite->set_position(
            ( BWIDTH - mAuthorNameYellow->get_width() ) / 2, y );

    /*  Position author email */
    mAuthorEmail->set_position(
            ( mAuthor->get_pos_x() + mAuthor->get_width() ) -
            mAuthorEmail->get_width(), y + 32 );

    /*  Position author website */
    mAuthorWebsite->set_position(
            ( mAuthor->get_pos_x() + mAuthor->get_width() ) -
            mAuthorWebsite->get_width(), y + 48 );

    /*  Set music author name position */
    mMusic1->set_position(
            ( BWIDTH - mMusic1->get_width() ) / 2,
            y + 96 );

    /*  Set music author website position */
    mMusic2->set_position(
            ( mMusic1->get_pos_x() + mMusic1->get_width() ) -
            mMusic2->get_width(),
            y + 120 );

    /*  Set the 'see credits.txt' position */
    mCredits->set_position(
            ( BWIDTH - mCredits->get_width() ) / 2,
            ( WHEIGHT - mCredits->get_height() ) - 16 );
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  What else?  This function renders everything to the screen
*/
void Credits::render( void )
{
    /*  Render author photograph */
    mAuthor->render_self();

    /*  Render author name (pulsing white) */
    render_pulse( mAuthorNameYellow, mAuthorNameWhite, 4 );

    /*  Render border */
    render_texture_border( mAuthor );

    /*  Render author email and website */
    mAuthorEmail->render_self();
    mAuthorWebsite->render_self();

    /*  Render music author stuff */
    mMusic1->render_self();
    mMusic2->render_self();

    /*  Render the 'see credits.txt' texture */
    mCredits->render_self();
}
