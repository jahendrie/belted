#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
*/
Panel::Panel( void )
{
    /*  Init panel position */
    mPos.x = mPos.y = 0;

    /*  Init panel dimensions */
    mWidth = mHeight = 0;

    /*  Init panel element relative positions */
    init_layout();

    /*  Init texture clips */
    init_clips();

    /*  Null texture object pointers */
    mTextureBackground = NULL;
    mTextureButtons = NULL;
    mScoreTexture = NULL;
    mHighScoreTexture = NULL;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Panel::~Panel( void )
{
    /*
     *  Null the texture object pointers.  Note that the texture objects aren't
     *  being deleted here because they exist outside of this class and are
     *  freed in the close() function.
     */
    mTextureBackground = NULL;
    mTextureButtons = NULL;
    mScoreTexture = NULL;
    mHighScoreTexture = NULL;
}



/*
--------------------------------------------------------------------------------
                                   INIT CLIPS
--------------------------------------------------------------------------------
 *  Initialize the array of clips for the panel buttons
*/
void Panel::init_clips( void )
{
    for( int i = BUTTON_OFF; i < TOTAL_PANEL_BUTTONS; ++i )
    {
        mButtonClips[ i ].x = 0;
        mButtonClips[ i ].y = i * 32;
        mButtonClips[ i ].w = 32;
        mButtonClips[ i ].h = 32;
    }
}


/*
--------------------------------------------------------------------------------
                                  LAYOUT STUFF
--------------------------------------------------------------------------------
 *  Position the score texture relative point values
*/
void Panel::init_layout( void )
{
    mScorePos.x = 76;
    mScorePos.y = 50;

    mHighScorePos.x = 270;
    mHighScorePos.y = 50;
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
 *  Set the positions of the score textures according to both their relative
 *  positions on the panel and the absolute position of the panel itself.
*/
void Panel::layout( void )
{
    /*  Current score position */
    mScoreTexture->set_position( mPos.x + mScorePos.x, mPos.y + mScorePos.y );

    /*  Current high score */
    mHighScoreTexture->set_position( mPos.x + mHighScorePos.x,
            mPos.y + mHighScorePos.y );
}


/*
--------------------------------------------------------------------------------
                              SET / GET DIMENSIONS
--------------------------------------------------------------------------------
*/
void Panel::set_width( int width )
{
    mWidth = width;
}

void Panel::set_height( int height )
{
    mHeight = height;
}


int Panel::get_width( void )
{
    return( mWidth );
}

int Panel::get_height( void )
{
    return( mHeight );
}



/*
--------------------------------------------------------------------------------
                               SET / GET POSITION
--------------------------------------------------------------------------------
*/
void Panel::set_position( int x, int y )
{
    mPos.x = x;
    mPos.y = y;
}

int Panel::get_pos_x( void )
{
    return( mPos.x );
}

int Panel::get_pos_y( void )
{
    return( mPos.y );
}



/*
--------------------------------------------------------------------------------
                               SET TEXTURE OBJECTS
--------------------------------------------------------------------------------
 *  The texture object pointers, as can be seen here, are set from outside this
 *  class.
*/
void Panel::set_panel_texture_background( Texture *texture )
{
    mTextureBackground = texture;
}

void Panel::set_panel_texture_buttons( Texture *texture )
{
    mTextureButtons = texture;
}

void Panel::set_score_texture_object( Texture *texture )
{
    mScoreTexture = texture;
}

void Panel::set_high_score_texture_object( Texture *texture )
{
    mHighScoreTexture = texture;
}



/*
--------------------------------------------------------------------------------
                                    SET RECT
--------------------------------------------------------------------------------
 *  Set the draw rect according to the X and Y positions given
*/
void Panel::set_rect( int x, int y )
{
    mDrawRect.x = x;
    mDrawRect.y = y;
    mDrawRect.w = 20;
    mDrawRect.h = 20;

}


/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Panel::render( void )
{
    /*  These are used for button displays on the panel */
    int livesCount = player.get_lives();
    int chargeCount = player.get_charge();

    /*  Render the background */
    mTextureBackground->render( mPos.x, mPos.y, mWidth, mHeight );

    /*  -------------   BUTTONS -------- */
    /*
     *  Yeah, it's a bit of a mess.  Lots of magic numbers, I know.  These
     *  numbers represent countless minutes of fiddling with positions and
     *  recompiling the program, over and over, to see what 'looks right'.
     */

    /*
     *  ------------    The lives meter
     */
    int offsetY = mPos.y + 16;      //  Grab Y offset
    for( int offsetX = BWIDTH - 220; offsetX < BWIDTH - 50; offsetX += 36 )
    {
        /*  If lives are in the positive, render the 'on' button sprites */
        if( livesCount > 0 )
        {
            mTextureButtons->render( offsetX, offsetY, 24, 24,
                    &mButtonClips[ BUTTON_ON ] );

            /*  Decrement the livesCount var so that it isn't all green orbs */
            --livesCount;
        }

        /*  Once livesCount is down, render the remainder as 'off' buttons */
        else
        {
            mTextureButtons->render( offsetX, offsetY, 24, 24,
                    &mButtonClips[ BUTTON_OFF ] );
        }
    }

    /*
     *  ------------    The charge meter
     */
    offsetY += 40;      //  Adjust Y offset
    for( int offsetX = BWIDTH - 220; offsetX < BWIDTH - 50; offsetX += 36 )
    {
        /*
         *  This is similar to how the lives meter was taken care of above, but
         *  slightly different since a fully charged 'charge' meter is green,
         *  whereas it's yellow while it's still charging up.  Meaning, if we're
         *  fully charged, all 'on' buttons; if we're not, but greater than 0,
         *  yellow buttons for the ones that are on, 'off' buttons for all the
         *  others.
         */
        if( chargeCount == 5 )
        {
            mTextureButtons->render( offsetX, offsetY, 24, 24,
                    &mButtonClips[ BUTTON_ON ] );
        }
        else if( chargeCount > 0 )
        {
            mTextureButtons->render( offsetX, offsetY, 24, 24,
                    &mButtonClips[ BUTTON_CHARGING ] );

            --chargeCount;
        }
        else
        {
            mTextureButtons->render( offsetX, offsetY, 24, 24,
                    &mButtonClips[ BUTTON_OFF ] );
        }
    }

    /*  -----------------       TEXT TEXTURES   --------------------- */
    scoreText->render_self();
    highScoreText->render_self();
}
