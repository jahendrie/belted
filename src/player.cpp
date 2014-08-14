/*******************************************************************************
 *  player.cpp
 *
 *  This file defines the player class, which inherits from the ship class.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                  INIT PLAYER
--------------------------------------------------------------------------------
 *  This is the master init function for the player object.  It initializes the
 *  player stats, as well as the texture object pointers, color and sfx channel.
 *  Basically, anything that only needs to be initialized once goes here.
*/
void Player::init_player( void )
{
    /*  Initialize the player stats */
    init_player_stats();

    /*  Init normal and special texture objects */
    mNormalTextureObject = NULL;
    mSpecialTextureObject = NULL;

    /*  Set the color to white */
    mCurrentColor = &colors[ COLOR_WHITE ];

    /*  Set the default SFX channel to 0... why not. */
    mChannel = 0;

    /*  Set current velocity to 0 by default */
    mVelocity.x = mVelocity.y = 0;
    mMaxVelocity = 32;
    mMinVelocity = -32;
    mMidVelocity = 0;
}



/*
--------------------------------------------------------------------------------
                               INIT PLAYER STATS
--------------------------------------------------------------------------------
 *  Initializes all player stats.
*/
void Player::init_player_stats( void )
{
    /*  This ship does indeed belong to the player */
    mPlayer = true;

    /*  Player starts out with three lives */
    mDefaultLives = 3;
    mLives = mDefaultLives;
    mMaxLives = 5;

    /*  Player starts out with zero charge */
    mCharge = 0;
    mMaxCharge = 5;
    mChargeFull = false;

    /*  Invulnerability stuff */
    mInvulnerable = false;
    mInvulnerableTicks = 0;

    /*  Power stuff */
    mPowered = false;
    mPoweringDown = false;
    mPowerTicks = 0;
    mPowerMaxTicks = 900;       //  Approx 15 seconds
}




/*
--------------------------------------------------------------------------------
                                  RESET STATS
--------------------------------------------------------------------------------
 *  Reset player stats; similar to the above function, but only stuff that
 *  really needs to be reset after every game over.
*/
void Player::reset_stats( void )
{
    mAlive = true;              //  Make player live
    mLives = mDefaultLives;     //  Reset the lives counter
    mCharge = 0;                //  Set charge meter to zero
    mChargeFull = false;        //  Charge meter obviously isn't full if it's 0
    mPowered = false;           //  Player is not 'powered' when they restart
    mPowerTicks = 0;            //  Power ticks is reset to zero
    mPoweringDown = false;      //  This doesn't need to be true right now
    mInvulnerable = true;       //  Temporary invulnerability is switch on
    mExploding = false;         //  They don't start off exploding
}



/*
--------------------------------------------------------------------------------
                                INCREMENT LIVES
--------------------------------------------------------------------------------
*/
void Player::increment_lives( void )
{
    /*  If they player is allowed more lives */
    if( mLives < mMaxLives )
    {
        /*  Increment their current number of lives */
        ++mLives;

        /*  Play the 'extra life' sound effect */
        Mix_PlayChannel( -1, soundEffectExtraLife, 0 );
    }
}



/*
--------------------------------------------------------------------------------
                                  CHECK BOUNDS
--------------------------------------------------------------------------------
 *  Checks the player's position against the play boundaries of the screen
*/
void Player::check_bounds( void )
{
    /*  Check X position boundaries */
    if( mPos.x < 0 )
        mPos.x = 0;
    else if( mPos.x + mWidth > BWIDTH )
        mPos.x = BWIDTH - mWidth;

    /*  Check Y position boundaries */
    if( mPos.y < 0 )
        mPos.y = 0;
    else if( mPos.y + mHeight > BHEIGHT )
        mPos.y = BHEIGHT - mHeight;
}



/*
--------------------------------------------------------------------------------
                                   MOVE MOUSE
--------------------------------------------------------------------------------
 *  The player object has no proper event handling really.  This function is
 *  called directly from the main events loop; other player actions (honking,
 *  etc.) are handled there as well.
*/
void Player::move_mouse( void )
{
    /*
     *  We just store the current mouse position directly into the player's
     *  current position.
     */
    SDL_GetMouseState( &mPos.x, &mPos.y );

    /*  Check bounds to make sure we're cool, man */
    check_bounds();
}



/*
--------------------------------------------------------------------------------
                                 MOVE VELOCITY
--------------------------------------------------------------------------------
 *  This moves the player's ship according to its velocity, which is altered by
 *  keyboard input (and time).  It only exists to keep keyboard movement a bit
 *  smoother than it might otherwise be.
*/
void Player::move_velocity( void )
{
    /*  Adjust the player's position */
    mPos.x += mVelocity.x / 2;
    mPos.y += mVelocity.y / 2;

    /*  Correct the X velocity */
    if( mVelocity.x < mMinVelocity )
        mVelocity.x = mMinVelocity;
    else if( mVelocity.x > mMaxVelocity )
        mVelocity.x = mMaxVelocity;

    /*  Correct the Y velocity */
    if( mVelocity.y < mMinVelocity )
        mVelocity.y = mMinVelocity;
    else if( mVelocity.y > mMaxVelocity )
        mVelocity.y = mMaxVelocity;

    /*  Check player position against level boundaries */
    check_bounds();
}



/*
--------------------------------------------------------------------------------
                               KEYBOARD MOVEMENT
--------------------------------------------------------------------------------
 *  This function is called from outside the event polling loop to prevent
 *  input delays.  It adjusts the player's current velocity according to the
 *  input read from SDL_GetKeyboardState().
*/
void Player::move_keyboard( void )
{
    /*  Get a state of all keys current being pressed */
    const Uint8 *state = SDL_GetKeyboardState( NULL );

    /*  ----------------    HORIZONTAL VELOCITY --------------- */
    /*  Left key */
    if( state[ SDL_SCANCODE_LEFT ] )
    {
        if( mVelocity.x > mMidVelocity )
            mVelocity.x = mMidVelocity;
        else
            --mVelocity.x;
    }

    /*  Right key */
    else if( state[ SDL_SCANCODE_RIGHT ] )
    {
        if( mVelocity.x < mMidVelocity )
            mVelocity.x = mMidVelocity;
        else
            ++mVelocity.x;
    }

    /*  If they aren't pressing left or right, cancel horizontal velocity */
    else
        mVelocity.x = mMidVelocity;



    /*  ----------------    VERTICAL VELOCITY ------------------ */
    /*  Up key */
    if( state[ SDL_SCANCODE_UP ] )
    {
        if( mVelocity.y > mMidVelocity )
            mVelocity.y = mMidVelocity;
        else
            --mVelocity.y;
    }

    /*  Down key */
    else if( state[ SDL_SCANCODE_DOWN ] )
    {
        if( mVelocity.y < mMidVelocity )
            mVelocity.y = mMidVelocity;
        else
            ++mVelocity.y;
    }

    /*  If they aren't moving up/down, cancel vertical velocity */
    else
        mVelocity.y = mMidVelocity;


    //  Now, we actually move the ship in accordance with the adjusted velocity
    move_velocity();
}




/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  All the update function does is keep the honking bool in line.
*/
void Player::update( void )
{
    if( mHonking )
        mHonking = false;
}



/*
--------------------------------------------------------------------------------
                                      KILL
--------------------------------------------------------------------------------
 *  Murder the player
*/
void Player::kill( void )
{
    /*  Subract one life */
    --mLives;

    /*  Start the explosion */
    init_explosion();

    /*  Make the screen flash */
    screenFlash = true;

    /*  Play the explosion sound effect */
    Mix_PlayChannel( -1, soundEffectExplosion, 0 );

    /*  Set the current charge to zero */
    mCharge = 0;
    mChargeFull = false;
    chargeScore = 0;

    /*  If the player is out of lives, game over */
    if( mLives == 0 )
        game_over();
}


/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  Master render function that determines which rendering function to call
 *  depending on the player's current state.
*/
void Player::render( void )
{
    if( mAlive )
    {
        if( mInvulnerable )
            render_invulnerable();
        else
            render_alive();
    }

    else if( mExploding )
        render_exploding();
}


/*
--------------------------------------------------------------------------------
                                  RENDER ALIVE
--------------------------------------------------------------------------------
 *  Render the player while alive (normal).
*/
void Player::render_alive( void )
{
    mTextureObject->render( mPos.x, mPos.y, mWidth, mHeight, &mClips[ mFrame ]);
}



/*
--------------------------------------------------------------------------------
                              RENDER INVULNERABLE
--------------------------------------------------------------------------------
 *  Render the player while temporarily invulnerable; 'flashing' right after
 *  respawning
*/
void Player::render_invulnerable( void )
{
    ++mInvulnerableTicks;

    if( mInvulnerableTicks % 4 == 0 )
        mTextureObject->mod_alpha( 0 );
    else
        mTextureObject->mod_alpha( 255 );

    if( mInvulnerableTicks > 180 )
    {
        mInvulnerable = false;
        mInvulnerableTicks = 0;
    }

    render_alive();
}



/*
--------------------------------------------------------------------------------
                           GET / SET INVULNERABILITY
--------------------------------------------------------------------------------
*/
bool Player::is_invulnerable( void )
{
    return( mInvulnerable );
}


void Player::set_invulnerable( bool invulnerable )
{
    mInvulnerable = invulnerable;
}



/*
--------------------------------------------------------------------------------
                                      TILT
--------------------------------------------------------------------------------
 *  This affects the clip in the player texture currently being rendered.
 *  Essentially, if the player is moving left, move 'upward' along the player
 *  ship texture by moving back along the clip array.  If he's moving right,
 *  move down the texture by moving foward along the clip array.
 *
 *  Basically, it tilts the ship left or right.
 *
 *  It might be helpful to mention that the player texture is one long, vertical
 *  sprite sheet, 30 rows, 1 column.
*/
void Player::tilt( void )
{
    /*  We'll store the relative mouse motion here */
    int change = 0;

    /*  DO IT TO IT */
    SDL_GetRelativeMouseState( &change, NULL );

    /*  Also check for 'keyboard' velocity */
    if( mVelocity.x < 0 )
        change = -1;
    else if( mVelocity.x > 0 )
        change = 1;

    /*  If the player has moved left */
    if( change < 0 )
    {
        /*  Tilt left */
        if( mFrame > 0 )
            --mFrame;
    }

    /*  If the player has moved right */
    else if( change > 0 )
    {
        /*  Tilt right */
        if( mFrame < mMaxFrames-1 )
            ++mFrame;
    }

    /*  Otherwise, just return to the upright position (frame 15) */
    else
    {
        if( mFrame < 15 )
            ++mFrame;
        else if( mFrame > 15 )
            --mFrame;
    }
}



/*
--------------------------------------------------------------------------------
                                SET / GET CHARGE
--------------------------------------------------------------------------------
*/
void Player::set_charge( int charge )
{
    /*  Set the charge to what was given */
    mCharge = charge;

    /*  Correct the charge if it's too little */
    if( mCharge < 0 )
        mCharge = 0;

    /*  Or too great */
    else if( mCharge > mMaxCharge )
        mCharge = mMaxCharge;
}


int Player::get_charge( void )
{
    return( mCharge );
}


bool Player::is_charged( void )
{
    return( mChargeFull );
}



/*
--------------------------------------------------------------------------------
                                INCREMENT CHARGE
--------------------------------------------------------------------------------
 *  Just tick the charge up one
*/
void Player::increment_charge( void )
{
    /*  If the charge can be increased */
    if( mCharge < mMaxCharge )
    {
        /*  Increase it */
        ++mCharge;

        /*  We now set the charge as 'full' if it is */
        if( mCharge == mMaxCharge && mChargeFull == false )
        {
            mChargeFull = true;
            Mix_PlayChannel( -1, soundEffectDing, 0 );
        }

        /*  If it isn't full, just play a 'tick' sound */
        else
            Mix_PlayChannel( -1, soundEffectTick, 0 );
    }

}


/*
--------------------------------------------------------------------------------
                           SET SPECIAL TEXTURE OBJECT
--------------------------------------------------------------------------------
 *  This is a second texture object, used as a base texture to be altered while
 *  the player is 'powered up'.
*/
void Player::set_special_texture_object( Texture *texture )
{
    mSpecialTextureObject = texture;
}



/*
--------------------------------------------------------------------------------
                                INIT / END POWER
--------------------------------------------------------------------------------
 *  Start the 'power up' process
*/
void Player::init_power( void )
{
    /*  Can't be powered if you're dead */
    if( mAlive )
    {
        /*  Or if you don't have enough charge */
        if( mChargeFull )
        {
            /*  'Save' the normal texture */
            mNormalTextureObject = mTextureObject;

            /*  Set current texture to special texture */
            mTextureObject = mSpecialTextureObject;

            /*  Make player invulnerable / powered */
            mInvulnerable = true;
            mPowered = true;
            mPoweringDown = false;

            /*  Set charge to zero */
            mCharge = 0;
            mChargeFull = false;

            /*  Increase game speed */
            warp_up();

            /*  Active tail particles */
            tail.start_tail();

            /*  Engine spool up sound effect */
            mChannel = Mix_PlayChannel( -1, soundEffectEngineUp, 0 );
        }

        /*  If not enough charge, just play an 'engine fail' sound effect */
        else
        {
            /*  Engine fail sound effect */
            mChannel = Mix_PlayChannel( -1, soundEffectEngineFail, 0 );
        }
    }
}



/*
--------------------------------------------------------------------------------
                                   END POWER
--------------------------------------------------------------------------------
 *  This happens at the very end of 'powering down', reseting the special
 *  texture to its default and making the player vulnerable again
*/
void Player::end_power( void )
{
    if( mPowered )
    {
        /*  Reset special texture color mod */
        mSpecialTextureObject->set_color_mod( 255, 255, 255 );

        /*  Reset texture back to normal */
        mTextureObject = mNormalTextureObject;

        /*  Set invulnerability and powered status back to false */
        mPowered = false;
        mInvulnerable = false;

        /*  Reset powered ticks */
        mPowerTicks = 0;

        /*  Deactivate tail */
        tail.stop_tail();
    }
}



/*
--------------------------------------------------------------------------------
                                  POWER UPDATE
--------------------------------------------------------------------------------
 *  This function is called while the player is currently powered up.
*/
void Player::power_update( void )
{
    /*  Update the color every 5 ticks */
    if( mPowerTicks % 5 == 0 )
    {
        /*  Cycle color */
        int currentColor;
        for( currentColor = 0; currentColor < COLOR_BLACK; ++currentColor )
        {
            /*
             *  If we hit the 'current color' in the colors array, move along to
             *  the next color in the array that isn't black.
             */
            if( mCurrentColor == &colors[ currentColor ] )
            {
                /*  If the next one isn't black */
                if( currentColor + 1 < COLOR_BLACK )
                    mCurrentColor = &colors[ currentColor + 1 ];

                /*  Otherwise, go back to the beginning (white) */
                else
                    mCurrentColor = &colors[ COLOR_WHITE ];

                /*  Exit the loop since we don't need to continue through it */
                break;
            }
        }

        /*  Set the color */
        mSpecialTextureObject->set_color_mod( mCurrentColor->r,
                mCurrentColor->g, mCurrentColor->b );
    }

    /*  Increment ticks */
    ++mPowerTicks;

    /*
     *  If we've almost reached our allotted ticks, start flashing to warn the
     *  player that they're almost out of time; this is determined to be during
     *  the period between 75% of the player's allotted time and the 100% of the
     *  allotted time.
     */
    if( mPowerTicks > ( mPowerMaxTicks * 0.75f ) &&
            mPowerTicks < mPowerMaxTicks )
    {
        /*  Every four ticks, flash on or off */
        if( mPowerTicks % 4 == 0 )
        {
            if( mTextureObject == mNormalTextureObject )
                mTextureObject = mSpecialTextureObject;
            else
                mTextureObject = mNormalTextureObject;
        }

        /*  Reset game speed */
        if( maxWarpSpeed > 1 )
        {
            warp_down();
        }

        /*  Play the spool down sound effect if appropriate */
        if( ! mPoweringDown )
        {
            /*  If the spool up sound effect is playing, stop it */
            if( Mix_Playing( mChannel ) == 1 )
                Mix_HaltChannel( mChannel );

            /*  Play the spool down sound effect */
            Mix_PlayChannel( mChannel, soundEffectEngineDown, 0 );

            mPoweringDown = true;
        }

    }

    /*  Otherwise, if we're out of time, reset everything we need to */
    else if( mPowerTicks > mPowerMaxTicks )
        end_power();
}



/*
--------------------------------------------------------------------------------
                                   IS POWERED
--------------------------------------------------------------------------------
*/
bool Player::is_powered( void )
{
    return( mPowered );
}


/*
--------------------------------------------------------------------------------
                            SET / GET SPECIAL COLOR
--------------------------------------------------------------------------------
*/
void Player::set_special_color( SDL_Color *color )
{
    mCurrentColor = color;
}


SDL_Color* Player::get_special_color( void )
{
    return( mCurrentColor );
}



/*
--------------------------------------------------------------------------------
                                      HONK
--------------------------------------------------------------------------------
*/
void Player::honk( void )
{
    if( mAlive )
    {
        /*  Set honking status */
        mHonking = true;

        Mix_PlayChannel( -1, soundEffectHonk, 0 );
    }
}


bool Player::is_honking( void )
{
    return( mHonking );
}
