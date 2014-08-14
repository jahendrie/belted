/*******************************************************************************
 *  ship.cpp
 *
 *  This file contains function definitions for the ship class, which is the
 *  parent class for both the player class and the enemy class.
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
Ship::Ship( void )
{
    /*  Null our pointer */
    mTextureObject = NULL;

    /*  Set all of our whatevers to 0 */
    mWidth = mHeight = mPos.x = mPos.y = 0;

    /*  Set frames */
    mFrame = mMaxFrames = 0;

    /*  Initialize our colliders */
    init_colliders();

    /*  The starts out alive and not exploding */
    mAlive = true;
    mDefaultLives = 1;
    mLives = mDefaultLives;
    mMaxLives = 1;
    mExploding = false;

    /*  By default, a ship is not initialized as a player ship */
    mPlayer = false;

    /*  Ships are not, by default, invulnerable */
    mInvulnerable = false;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Ship::~Ship( void )
{
    /*  Null the texture object pointer */
    mTextureObject = NULL;

    /*  Reset all of our things to 0 */
    mWidth = mHeight = mPos.x = mPos.y = 0;
}


/*
--------------------------------------------------------------------------------
                               SET TEXTURE OBJECT
--------------------------------------------------------------------------------
*/
void Ship::set_texture_object( Texture *texture )
{
    mTextureObject = texture;
}


/*
--------------------------------------------------------------------------------
                              SET / GET DIMENSIONS
--------------------------------------------------------------------------------
*/
void Ship::set_width( int width )
{
    mWidth = width;
}

void Ship::set_height( int height )
{
    mHeight = height;
}

int Ship::get_width( void )
{
    return( mWidth );
}

int Ship::get_height( void )
{
    return( mHeight );
}

int Ship::get_texture_width( void )
{
    /*
     *  We init this to -1 as a way to determine if this object doesn't have a
     *  texture object assigned to it.  Theoretically.
     */
    int width = -1;

    if( mTextureObject != NULL )
        width = mTextureObject->get_texture_width();

    return( width );
}

int Ship::get_texture_height( void )
{
    int height = -1;

    if( mTextureObject != NULL )
        height = mTextureObject->get_texture_height();

    return( height );
}


/*
--------------------------------------------------------------------------------
                               SET / GET POSITION
--------------------------------------------------------------------------------
*/
void Ship::set_position( int x, int y )
{
    mPos.x = x;
    mPos.y = y;
}

int Ship::get_pos_x( void )
{
    return( mPos.x );
}

int Ship::get_pos_y( void )
{
    return( mPos.y );
}


/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Ship::render( void )
{
    mTextureObject->render( mPos.x, mPos.y, mWidth, mHeight, &mClips[ mFrame ]);
}





/*
--------------------------------------------------------------------------------
                                    GET RECT
--------------------------------------------------------------------------------
 *  Return the rect (containing position and dimensions) of the ship
*/
SDL_Rect Ship::get_rect( void )
{
    SDL_Rect rect;
    rect.x = mPos.x;
    rect.y = mPos.y;
    rect.w = mWidth;
    rect.h = mHeight;

    return( rect );
}



/*
--------------------------------------------------------------------------------
                                     FRAMES
--------------------------------------------------------------------------------
 *  The frame determines which clip of the texture to display currently
*/
void Ship::set_max_frames( int frames )
{
    mMaxFrames = frames;
}

void Ship::set_current_frame( int frame )
{
    mFrame = frame;
}

int Ship::get_max_frames( void )
{
    return( mMaxFrames );
}

int Ship::get_current_frame( void )
{
    return( mFrame );
}



/*
--------------------------------------------------------------------------------
                                   INIT CLIPS
--------------------------------------------------------------------------------
 *  Initialize all of the clips for the ship's texture
*/

/*  -----   This function handles textures laid out with colums and rows */
void Ship::init_clips( int rows, int columns, int width, int height )
{
    for( int r = 0; r < rows; ++r )
    {
        for( int c = 0; c < columns; ++c )
        {
            mClips[ ( r * columns ) + c ].x = c * width;
            mClips[ ( r * columns ) + c ].y = r * height;
            mClips[ ( r * columns ) + c ].w = width;
            mClips[ ( r * columns ) + c ].h = height;
        }
    }
}


/*  --------    This function deals with 1-column, multi-row textures */
void Ship::init_clips_vertical( int width, int height, int frames )
{
    for( int i = 0; i < frames; ++i )
    {
        mClips[ i ].x = 0;
        mClips[ i ].y = i * height;
        mClips[ i ].w = width;
        mClips[ i ].h = height;
    }
}



/*
--------------------------------------------------------------------------------
                                 INIT COLLIDERS
--------------------------------------------------------------------------------
 *  Initialize the ship's colliders to default values (0)
*/
void Ship::init_colliders( void )
{
    /*  Init circular collider */
    mColliderCircle.x = mColliderCircle.y = mColliderCircle.r = 0;

    /*  Init rectangular collider */
    mColliderRect.x = mColliderRect.y = mColliderRect.w = mColliderRect.h = 0;
}



/*
--------------------------------------------------------------------------------
                             INIT CIRCULAR COLLIDER
--------------------------------------------------------------------------------
 *  Create the ship's circular collider according to given radius
*/
void Ship::init_collider_circ( int radius )
{
    mColliderCircle.x = mPos.x;
    mColliderCircle.y = mPos.y;
    mColliderCircle.r = radius;
}



/*
--------------------------------------------------------------------------------
                           INIT RECTANGULAR COLLIDER
--------------------------------------------------------------------------------
 *  Create the ship's rectangular collider according to given width and height
*/
void Ship::init_collider_rect( int width, int height )
{
    mColliderRect.x = mPos.x;
    mColliderRect.y = mPos.y;
    mColliderRect.w = width;
    mColliderRect.h = height;
}



/*
--------------------------------------------------------------------------------
                                ADJUST COLLIDERS
--------------------------------------------------------------------------------
 *  Adjust the ship's colliders to match the position of the ship
*/
void Ship::adjust_colliders( void )
{
    /*  Adjust rectangular collider */
    mColliderRect.x = mPos.x;
    mColliderRect.y = mPos.y;

    /*  Adjust circular collider */
    mColliderCircle.x = mPos.x;
    mColliderCircle.y = mPos.y;
}



/*
--------------------------------------------------------------------------------
                                RETURN COLLIDERS
--------------------------------------------------------------------------------
 *
*/
Circle& Ship::get_collider_circ( void )
{
    return( mColliderCircle );
}

SDL_Rect& Ship::get_collider_rect( void )
{
    return( mColliderRect );
}




/*
--------------------------------------------------------------------------------
                              INIT PIXEL COLLIDERS
--------------------------------------------------------------------------------
 *  Here we initialize the ship's collider rects vector to match those of its
 *  texture object
*/
void Ship::init_pixel_colliders( void )
{
    for( int i = 0; i < 30; ++i )
    {
        mColliders[ i ] = mTextureObject->get_pixel_collider( i );
    }
}



/*
--------------------------------------------------------------------------------
                              TRANSLATE COLLIDERS
--------------------------------------------------------------------------------
 *  This function scales the colliders to match the ship's own scale; the number
 *  of colliders is scaled, as are the dimensions and positions of each collider
 *  retained
*/
void Ship::translate_colliders( int scale )
{
    /*
     *  Here we create a new, temporary collider rects vector to store the data
     *  from the texture object's own corresponding colliders.  We do this for
     *  as many frames as are relevant to the particular instance calling this
     *  method.
     */
    std::vector<Collider> tColliders[ mMaxFrames ];
    for( int i = 0; i < mMaxFrames; ++i )
    {
        tColliders[ i ] = mTextureObject->get_pixel_collider( i );
    }

    /*
     *  Go through the ship object's vector of colliders, scaling the
     *  corresponding temporary (local) texture colliders to match the ship's
     *  scale, including relative collider rect location, the positions and the
     *  dimensions.
     */
    for( int f = 0; f < mMaxFrames; ++f )
    {
        mColliders[ f ].clear();

        for( unsigned int c = 0; c < tColliders[ f ].size(); c += scale )
        {
            Collider collider;
            collider.x = (tColliders[ f ][ c ].x / scale);
            collider.y = c/scale;
            collider.w = tColliders[ f ][ c ].w / scale;
            collider.h = 1;

            mColliders[ f ].push_back( collider );
        }
    }
}



/*
--------------------------------------------------------------------------------
                              GET PIXEL COLLIDERS
--------------------------------------------------------------------------------
 *  Return a fresh copy of the colliders vector
*/
std::vector<Collider> Ship::get_pixel_collider( int frame )
{
    std::vector<Collider> colliders;

    for( int i = 0; i < mHeight; ++i )
    {
        Collider collider;
        collider.x = mColliders[ frame ][ i ].x + mPos.x;
        collider.y = mColliders[ frame ][ i ].y + mPos.y;
        collider.w = mColliders[ frame ][ i ].w;
        collider.h = 1;

        colliders.push_back( collider );
    }

    return( colliders );
}



/*
--------------------------------------------------------------------------------
                                 INIT EXPLOSION
--------------------------------------------------------------------------------
*/
void Ship::init_explosion( void )
{
    /*  choices[ rand() % 2 ] will yield either a negative or a positive one */
    int choices[] = { -1, 1 };

    /*  The number of particles to draw -- min 20, max 99 */
    mParticlesToDraw = ( rand() % 80 ) + 20;

    /*  For each type of debris */
    for( int c = 0; c < TOTAL_DEBRIS; ++c )
    {
        for( int p = 0; p < mParticlesToDraw; ++p )
        {
            /*  Starting positions */
            mDebris[ c ][ p ].pos.x = ( mPos.x + ( mWidth / 2 ) +
                ((( rand() % 10 ) + 1 ) * choices[ rand() % 2 ] ));
            mDebris[ c ][ p ].pos.y = ( mPos.y + ( mHeight / 2 ) +
                ((( rand() % 10 ) + 1 ) * choices[ rand() % 2 ] ));

            /*  Ending positions */
            mDebris[ c ][ p ].end.x = ( mPos.x +
                ((( rand() % 400 ) + 1 ) * choices[ rand() % 2 ] ));
            mDebris[ c ][ p ].end.y = ( mPos.y +
                ((( rand() % 400 ) + 1 ) * choices[ rand() % 2 ] ));

            /*  Random velocity */
            mDebris[ c ][ p ].velocity.x = ( rand() % 5 ) + 1;
            mDebris[ c ][ p ].velocity.y = ( rand() % 5 ) + 1;

            /*  Direction */
            mDebris[ c ][ p ].direction.x = choices[ rand() % 2 ];
            mDebris[ c ][ p ].direction.y = choices[ rand() % 2 ];

            /*  Whether or not this particle 'twinkles' */
            bool val = false;
            choices[ rand() % 2 ] == 1 ? val = true : val = false;
            mDebris[ c ][ p ].twinkle = val;

            /*  Color is set according to current index in the upper for loop */
            switch( c )
            {
                case DEBRIS_WHITE:
                    mDebris[ c ][ p ].color = colors[ COLOR_WHITE ];
                    break;
                case DEBRIS_YELLOW:
                    mDebris[ c ][ p ].color = colors[ COLOR_YELLOW ];
                    break;
                case DEBRIS_ORANGE:
                    mDebris[ c ][ p ].color = colors[ COLOR_ORANGE ];
                    break;
                default:
                    mDebris[ c ][ p ].color = colors[ rand() % TOTAL_COLORS ];
                    break;
            }
        }


    }

    /*  Set 'exploding' to true, because the player is exploding */
    mExploding = true;

    /*  The player is dead now, so set mAlive to false */
    mAlive = false;
}


/*
--------------------------------------------------------------------------------
                            SET / GET PLAYER STATUS
--------------------------------------------------------------------------------
*/
void Ship::set_player( bool isPlayer )
{
    mPlayer = isPlayer;
}


bool Ship::is_player( void )
{
    return( mPlayer );
}



/*
--------------------------------------------------------------------------------
                                RENDER EXPLODING
--------------------------------------------------------------------------------
 *  Technically, this both renders and updates the explosion debris particles.
 *  I know, I know, I am a naughty little boy.
*/
void Ship::render_exploding( void )
{
    /*  Counters to determine if we're done rendering explosion particles */
    int done[ 4 ];
    for( int d = 0; d < 4; ++d )
        done[ d ] = 0;              //  Init to 0

    /*  For each particle that we're going to draw */
    for( int c = 0; c < TOTAL_DEBRIS; ++c )
    {
        for( int p = 0; p < mParticlesToDraw; ++p )
        {
            /*  Move the debris along the X axis */
            mDebris[ c ][ p ].pos.x += (
                    mDebris[ c ][ p ].velocity.x *
                    mDebris[ c ][ p ].direction.x );

            /*  Move the debris along the Y axis */
            mDebris[ c ][ p ].pos.y += (
                    mDebris[ c ][ p ].velocity.y *
                    mDebris[ c ][ p ].direction.y );

            /*
             *  We're using a separate integer for the alpha value because
             *  the Uint8s behave strangely when decreased to below zero; this
             *  is easier to work with.
             */
            int alpha = mDebris[ c ][ p ].color.a;      //  Set to alpha value
            alpha -= ( rand() % 3 ) + 4;                //  Decrease alpha

            /*  If the alpha falls to zero or less, set it to zero */
            if( alpha <= 0 )
            {
                ++done[ c ];    //  We're done with this array of particles
                alpha = 0;
            }

            /*  Twinkle */
            if( mDebris[ c ][ p ].twinkle )
            {
                /*  1 in 64 chance of twinkling */
                if( (rand() % 64) == 0 )
                {
                    if( alpha > 0 && alpha < 127 )
                        alpha += 127;
                }
            }

            /*  Set color alpha value */
            mDebris[ c ][ p ].color.a = alpha;

            /*  Set render draw color */
            SDL_SetRenderDrawColor( gRenderer,
                    mDebris[ c ][ p ].color.r,
                    mDebris[ c ][ p ].color.g,
                    mDebris[ c ][ p ].color.b,
                    mDebris[ c ][ p ].color.a );

            /*  Draw point */
            SDL_RenderDrawPoint( gRenderer,
                    mDebris[ c ][ p ].pos.x,
                    mDebris[ c ][ p ].pos.y );
        }
    }


    /*  Check to see if we're all done */
    bool allDone = true;
    for( int d = 0; d < 4; ++d )
    {
        if( done[ d ] < mParticlesToDraw )
        {
            allDone = false;
            break;
        }
    }

    /*  If we're done, end the explosion and continue play */
    if( allDone )
    {
        mExploding = false;

        if( mPlayer && mLives > 0 )
        {
            mAlive = true;
            mInvulnerable = true;
        }
    }
}


/*
--------------------------------------------------------------------------------
                                  IS EXPLODING
--------------------------------------------------------------------------------
*/
bool Ship::is_exploding( void )
{
    return( mExploding );
}



/*
--------------------------------------------------------------------------------
                                 DRAW COLLIDERS
--------------------------------------------------------------------------------
 *  This is only here for testing purposes, but I decided to keep it in because
 *  you never know, it could come in handy later.
*/
/*
void Ship::draw_colliders( std::vector<Collider> colliders )
{
    SDL_SetRenderDrawColor( gRenderer, 255, 0, 255, 127 );
    std::vector<Collider>::iterator it;
    for( it = colliders.begin(); it != colliders.end(); ++it )
    {
        SDL_Rect r;
        r.x = 100 + it->x;
        r.y = 100 + it->y;
        r.w = it->w;
        r.h = 1;

        SDL_RenderFillRect( gRenderer, &r );
    }
}

void Ship::draw_default_colliders( void )
{
    SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 127 );
    for( unsigned int c = 0; c < mColliders[ mFrame ].size(); ++c )
    {
        SDL_Rect r;
        r.x = mPos.x + mColliders[ mFrame ][ c ].x;
        r.y = mPos.y + mColliders[ mFrame ][ c ].y;
        r.w = mColliders[ mFrame ][ c ].w;
        r.h = mColliders[ mFrame ][ c ].h;

        if( r.w > 0 )
            SDL_RenderFillRect( gRenderer, &r );
    }
}
*/


/*
--------------------------------------------------------------------------------
                                     LIVES
--------------------------------------------------------------------------------
*/
void Ship::set_max_lives( int lives )
{
    mMaxLives = lives;
}

void Ship::set_default_lives( int lives )
{
    mDefaultLives = lives;
}

void Ship::set_lives( int lives )
{
    mLives = lives;
    mAlive = true;

    if( mLives < 0 )
    {
        mLives = 0;
        mAlive = false;
    }
    else if( mLives > mMaxLives )
        mLives = mMaxLives;
}

int Ship::get_default_lives( void )
{
    return( mDefaultLives );
}

int Ship::get_lives( void )
{
    return( mLives );
}

bool Ship::is_alive( void )
{
    return( mAlive );
}
