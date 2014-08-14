/*******************************************************************************
 *  initial.cpp
 *
 *  This file defines the initial class, which is used to create / load a
 *  texture that corresponds to one of the user's initials.  It also positions
 *  the texture, changes the letter, etc.
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
Initial::Initial( void )
{
    /*  Our texture object */
    mTextureObject = NULL;

    /*  Our letter, 'A' by default */
    mLetter = 'A';

    /*  Our booleans */
    mFlashing = false;
    mHasFocus = false;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Initial::~Initial( void )
{
    /*  Get rid of the texture */
    free_texture();

    /*  Null out the letter */
    mLetter = '\0';

    /*  Set the bools to false */
    mFlashing = false;
    mHasFocus = false;
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  This just calls another function that creates the letter texture, returning
 *  the success of said function.
*/
bool Initial::init( void )
{
    return( create_letter_texture() );
}




/*
--------------------------------------------------------------------------------
                                  FREE TEXTURE
--------------------------------------------------------------------------------
 *  Free the letter texture
*/
void Initial::free_texture( void )
{
    /*  If the texture isn't free, MAKE IT FREE */
    if( mTextureObject != NULL )
    {
        delete mTextureObject;
        mTextureObject = NULL;
    }
}


/*
--------------------------------------------------------------------------------
                                   SET LETTER
--------------------------------------------------------------------------------
 *  Set the letter to whatever was passed to the function, correcting for values
 *  that run out of bounds
*/
void Initial::set_letter( char letter )
{
    /*  If it's a capital letter */
    if( letter >= 'A' && letter <= 'Z' )
        mLetter = letter;

    /*  If it's a lowercase letter, subtract 32 to make it lowercase */
    else if( letter >= 'a' && letter <= 'z' )
        mLetter = letter - 32;

    /*  Otherwise, just set mLetter to capital A */
    else
        mLetter = 'A';
}



/*
--------------------------------------------------------------------------------
                                   GET LETTER
--------------------------------------------------------------------------------
*/
char Initial::get_letter( void )
{
    /*  Return the actual letter character */
    return( mLetter );
}



/*
--------------------------------------------------------------------------------
                                LETTER UP / DOWN
--------------------------------------------------------------------------------
*/
void Initial::letter_up( void )
{
    /*  Increment the letter character value */
    ++mLetter;

    /*  Correct the letter if the value went too high */
    if( mLetter > 'Z' )
        mLetter = 'A';

    /*  Recreate the letter texture */
    update_letter_texture();
}

void Initial::letter_down( void )
{
    /*  Decrement the letter character value */
    --mLetter;

    /*  Correct the letter if the value went too low */
    if( mLetter < 'A' )
        mLetter = 'Z';

    /*  Recreate the letter texture */
    update_letter_texture();
}



/*
--------------------------------------------------------------------------------
                               SET / GET FLASHING
--------------------------------------------------------------------------------
*/
void Initial::set_flashing( bool flashing )
{
    /*  Make the texture object flash */
    mTextureObject->set_flashing( flashing );
}

bool Initial::is_flashing( void )
{
    /*  Is the texture object flashing? */
    return( mTextureObject->is_flashing() );
}



/*
--------------------------------------------------------------------------------
                                SET / GET FOCUS
--------------------------------------------------------------------------------
*/
void Initial::set_focus( bool focus )
{
    mHasFocus = focus;
}

bool Initial::has_focus( void )
{
    return( mHasFocus );
}


/*
--------------------------------------------------------------------------------
                         CREATE / UPDATE LETTER TEXTURE
--------------------------------------------------------------------------------
*/
bool Initial::create_letter_texture( void )
{
    /*  Create the texture object */
    mTextureObject = new Texture();

    /*  Create a tiny string for our letter */
    char lStr[ 2 ];
    lStr[ 0 ] = mLetter;    //  The actual character value
    lStr[ 1 ] = '\0';       //  Null terminate it, just in case

    /*  Load the texture from the given string */
    if( ! mTextureObject->create_texture_from_string( gFont, lStr,
            colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create letter texture\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                             UPDATE LETTER TEXTURE
--------------------------------------------------------------------------------
 *  Same as create_letter_texture(), except it doesn't create the object
 *  anew, nor does it check for errors.  We're flying wild over here.
*/
void Initial::update_letter_texture( void )
{
    /*  Create a tiny string for our letter */
    char lStr[ 2 ];
    lStr[ 0 ] = mLetter;
    lStr[ 1 ] = '\0';

    /*  Create the texture object */
    mTextureObject->create_texture_from_string( gFont, lStr,
            colors[ COLOR_WHITE ] );
}



/*
--------------------------------------------------------------------------------
                               FLASH TICKS STUFF
--------------------------------------------------------------------------------
 *  Flash ticks are ticked down as the texture is rendered to determine when to
 *  render the normal texture or when to render nothing at all; this gives the
 *  appearance of the texture flashing on/off.
*/
void Initial::set_flash_ticks( int ticks )
{
    mTextureObject->set_flash_ticks( ticks );
}

void Initial::set_max_flash_ticks( int ticks )
{
    mTextureObject->set_max_flash_ticks( ticks );
}

int Initial::get_flash_ticks( void )
{
    return( mTextureObject->get_flash_ticks() );
}

int Initial::get_max_flash_ticks( void )
{
    return( mTextureObject->get_max_flash_ticks() );
}

int Initial::get_max_flash_ticks_default( void )
{
    return( mTextureObject->get_max_flash_ticks_default() );
}



/*
--------------------------------------------------------------------------------
                               GET TEXTURE OBJECT
--------------------------------------------------------------------------------
 *  Return the texture object pointer
*/
Texture* Initial::get_texture_object( void )
{
    return( mTextureObject );
}
