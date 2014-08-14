/*******************************************************************************
 *  enemy.cpp
 *
 *  This file defines the Enemy class, which inherits from the Ship class.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                   INIT ENEMY
--------------------------------------------------------------------------------
 *  Initializes key enemy attributes
*/
void Enemy::init_enemy( void )
{
    /*  Set current velocity and direction */
    mVelocity = 0;
    mDirection = 0;

    /*  Has this enemy been 'kissed'? */
    mKissed = false;

    /*  Default point values */
    mPointsKissed = 20;
    mPointsKilled = 50;
}



/*
--------------------------------------------------------------------------------
                               INIT POINT VALUES
--------------------------------------------------------------------------------
 *  This function defines how many points are earned by 'kissing' the enemy
 *  (honking at it while you're close) or destroying it.
*/
void Enemy::init_point_values( int scale, int velocity )
{
    /*  Smaller, faster asteroids are worth more points when kissed/killed */
    mPointsKissed += ( scale * 10 ) + ( velocity * 5 );
    mPointsKilled += ( scale * 15 ) + ( velocity * 5 );
}



/*
--------------------------------------------------------------------------------
                                    VELOCITY
--------------------------------------------------------------------------------
 *  Set or get the current velocity of the asteroid
*/
void Enemy::set_velocity( int velocity )
{
    /*  We can't allow for negative velocity values */
    if( velocity >= 0 )
        mVelocity = velocity;
}

int Enemy::get_velocity( void )
{
    return( mVelocity );
}



/*
--------------------------------------------------------------------------------
                                   DIRECTION
--------------------------------------------------------------------------------
 *  Set, get or flip direction
*/
void Enemy::set_direction( int direction )
{
    /*
     *  Positive values indicate a downward direction, while negative values
     *  indicate that the asteroid is moving 'backward' (up).  This doesn't
     *  actually happen in the game.
     *
     *  We only allow for values between -1 and +1, nothing lesser or greater.
     *  This is because this value will be multiplied by the velocity of the
     *  enemy to calculate distance up/down moved per tick.
     */
    if( direction >= 1 )
        mDirection = 1;
    else if( direction <= -1 )
        mDirection = -1;
    else
        mDirection = 0;
}

int Enemy::get_direction( void )
{
    return( mDirection );
}

void Enemy::flip_direction( void )
{
    mDirection *= -1;
}



/*
--------------------------------------------------------------------------------
                                      MOVE
--------------------------------------------------------------------------------
 *  Move the enemy along its Y axis down (or theoretically up) the screen
*/
void Enemy::move( void )
{
    mPos.y += ( mVelocity * mDirection ) * warpSpeed;
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  The update function is called during the 'update' loop in update.cpp.
 *  Update update update update.
 *
 *  All it does right now is move the enemy.
*/
void Enemy::update( void )
{
    move();
}


/*
--------------------------------------------------------------------------------
                                      KISS
--------------------------------------------------------------------------------
 *  This function defines what happens when the player 'kisses' an enemy.  In
 *  this game, a 'kiss' is when the player honks while near an asteroid to earn
 *  extra points.
 *
 *  The reason it's called a 'kiss' is because, initially, the player would earn
 *  these extra points just by flying near the asteroid; the terminology is an
 *  homage to those 'Aaaaaa' games.  The way the points were earned was changed
 *  because it was way too easy to rack up points initially, and I just haven't
 *  bothered to change the name.
*/
void Enemy::kiss( void )
{
    /*
     *  An enemy can only be kissed if it hasn't already been kissed (mKissed),
     *  the player is alive and the player isn't invulnerable (temporary
     *  invulnerability after respawn).
     */
    if( ! mKissed && player.is_alive() && ! player.is_invulnerable() )
    {
        /*  Create the kiss string of text */
        char kissString[ 16 ];
        snprintf( kissString, 16, "+%d", mPointsKissed );

        /*  Add this to the kissKills object thingy */
        kissKills.add( mPos.x, mPos.y, kissString, colors[ COLOR_GREEN ] );

        /*  This enemy has now been kissed */
        mKissed = true;

        /*  Play the kiss sound effect */
        Mix_PlayChannel( -1, soundEffectKiss, 0 );

        /*  Increase score counters appropriately */
        currentScore += mPointsKissed;
        extraLifeScore += mPointsKissed;

        /*  Also counts toward charge score if the player isn't charged */
        if( ! player.is_powered() )
            chargeScore += mPointsKissed;
    }
}



/*
--------------------------------------------------------------------------------
                                      KILL
--------------------------------------------------------------------------------
 *  This function defines what happens when an enemy is destroyed
*/
void Enemy::kill( void )
{
    /*  An enemy can't be killed if it's already dead, obviously */
    if( mAlive )
    {
        /*  Make the enemy dead */
        mAlive = false;

        /*  Increase score counters appropriately */
        currentScore += mPointsKilled;
        extraLifeScore += mPointsKilled;

        if( ! player.is_powered() )
            chargeScore += mPointsKilled;

        /*  Init general explosion */
        init_explosion();

        /*  Init special 'atari' explosion */
        AtariExplosion aExplosion;
        aExplosion.init( mPos.x, mPos.y, player.get_special_color() );
        aExplosions.push_back( aExplosion );

        /*  Create kill text texture string */
        char killString[ 16 ];
        snprintf( killString, 16, " +%d", mPointsKilled );

        /*  Add text to kiss/kill thingy */
        kissKills.add( mPos.x, mPos.y, killString, colors[ COLOR_HOT_PINK ] );

        /*  Play asteroid explosion sound effect */
        Mix_PlayChannel( -1, soundEffectExplosion2, 0 );
    }
}



/*
--------------------------------------------------------------------------------
                                  ALIVE STATUS
--------------------------------------------------------------------------------
 *  Set or get the enemy's current 'living' status
*/
void Enemy::live( void )
{
    mAlive = true;
}

bool Enemy::is_alive( void )
{
    return( mAlive );
}
