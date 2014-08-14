/*******************************************************************************
 *  texture.cpp
 *
 *  This file defines the Texture class, which is used to create/load textures,
 *  position textures, render textures and more.
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
Texture::Texture( void )
{
    /*  Point the texture pointer to nothing at all */
    mTexture = NULL;

    /*  Init default (loaded) dimensions */
    mTextureWidth = mTextureHeight = 0;

    /*  Init current (scaled) dimensions */
    mWidth = mHeight = 0;

    /*  Fade stuff */
    mFading = false;
    mFadeTicks = 0;

    /*  Flash stuff */
    mFlashing = false;
    mFlashTicks = 0;
    mMaxFlashTicks = 60;
    mMaxFlashTicksDefault = mMaxFlashTicks;

    /*  Does this object have focus */
    mHasFocus = false;
    
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Texture::~Texture( void )
{
    /*  All we need to do is free the texture */
    free_texture();
}


/*
--------------------------------------------------------------------------------
                                  FREE TEXTURE
--------------------------------------------------------------------------------
*/
void Texture::free_texture( void )
{
    /*  If the texture exists, kill it and null everything out */
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mTextureWidth = mTextureHeight = mWidth = mHeight = 0;
    }
}


/*
--------------------------------------------------------------------------------
                            CREATE TEXTURE FROM FILE
--------------------------------------------------------------------------------
 *  This method creates a texture from an image file (presumably a PNG since
 *  SDL_image was initialized with only that functionality).  It optionally
 *  generates colliders for sprite sheet images.
*/
bool Texture::create_texture_from_file( const char *path, bool clipping,
        int cWidth, int cHeight, int cCount )
{
    /*  Free the texture if it exists */
    free_texture();

    /*  Load a surface from the path provided */
    SDL_Surface *tempSurface = IMG_Load( path );
    if( tempSurface == NULL )
    {
        printf("ERROR:  Could not create surface from '%s':  IMG Error:  %s\n",
                path, IMG_GetError() );
        return( false );
    }

    /*  We save the pixel format for later use */
    if( gPixelFormat == 0 )
        gPixelFormat = (Uint32)tempSurface->format->format;

    /*  Now, create a texture from the loaded surface */
    mTexture = SDL_CreateTextureFromSurface( gRenderer, tempSurface );
    if( mTexture == NULL )
    {
        printf("ERROR:  Cannot create texture from surface.  SDL Error:  %s\n",
                SDL_GetError() );
        SDL_FreeSurface( tempSurface );
        return( false );
    }

    /*  Generate colliders */
    if( clipping )
    {
        for( int frame = 0; frame < cCount; ++frame )
        {
            generate_colliders( tempSurface, cWidth, frame );
        }

    }

    /*  Get dimensions from surface */
    mWidth = mTextureWidth = tempSurface->w;
    mHeight = mTextureHeight = tempSurface->h;

    /*  Free loaded surface */
    SDL_FreeSurface( tempSurface );

    /*  If we're here, we're good */
    return( true );
}


/*
--------------------------------------------------------------------------------
                           CREATE TEXTURE FROM STRING
--------------------------------------------------------------------------------
 *  This method creates a texture from a string of text using SDL_ttf.
*/
bool Texture::create_texture_from_string( TTF_Font *font, const char *string,
        SDL_Color textColor )
{
    /*  Free texture if it exists */
    free_texture();

    /*  Create a surface from rendered text */
    SDL_Surface *tempSurface = TTF_RenderText_Blended( font, string, textColor);
    if( tempSurface == NULL )
    {
        printf("ERROR:  Could not create rendered text.  TTF Error:  %s\n",
                TTF_GetError() );
        return( false );
    }

    /*  Create a texture from the loaded surface */
    mTexture = SDL_CreateTextureFromSurface( gRenderer, tempSurface );
    if( mTexture == NULL )
    {
        printf("ERROR:  Cannot create texture from surface.  SDL Error:  %s\n",
                SDL_GetError() );
        SDL_FreeSurface( tempSurface );
        return( false );
    }

    /*  Get dimensions from surface */
    mTextureWidth = mWidth = tempSurface->w;
    mTextureHeight = mHeight = tempSurface->h;

    /*  Free surface */
    SDL_FreeSurface( tempSurface );

    /*  We're good */
    return( true );
}


/*
--------------------------------------------------------------------------------
                              SET / GET DIMENSIONS
--------------------------------------------------------------------------------
*/
int Texture::get_texture_width( void )
{
    return( mTextureWidth );
}

int Texture::get_texture_height( void )
{
    return( mTextureHeight );
}

int Texture::get_width( void )
{
    return( mWidth );
}

int Texture::get_height( void )
{
    return( mHeight );
}


void Texture::set_width( int width )
{
    mWidth = width;
}


void Texture::set_height( int height )
{
    mHeight = height;
}



/*
--------------------------------------------------------------------------------
                                  RENDER SELF
--------------------------------------------------------------------------------
 *  This method has the texture render itself using its own position and
 *  dimensions.  Clipping is not supported.
*/
void Texture::render_self( void )
{
    SDL_Rect drawRect = { mPos.x, mPos.y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &drawRect );
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  This function renders the texture according to a given position, given
 *  dimensions and a given clip (default is NULL).
*/
void Texture::render( int x, int y, int width, int height, SDL_Rect *clip )
{
    /*  Create the draw rect for the texture */
    SDL_Rect drawRect = { x, y, width, height };

    /*  Copy the texture to the renderer */
    SDL_RenderCopy( gRenderer, mTexture, clip, &drawRect );
}



/*
--------------------------------------------------------------------------------
                                EXTENDED RENDER
--------------------------------------------------------------------------------
 *  This is similar to the above, except it takes in a drawRect rather than
 *  creating a new one from given positions/dimensions.  It does NOT actually
 *  call the SDL_RenderCopyEx function.
*/
void Texture::render_ext( SDL_Rect *drawRect, SDL_Rect *clip )
{
    SDL_RenderCopy( gRenderer, mTexture, clip, drawRect );
}



/*
--------------------------------------------------------------------------------
                                  RENDER FADE
--------------------------------------------------------------------------------
 *  This method is similar to render_self() except it also gets and modifies the
 *  alpha value of the texture instance, in effect, 'fading it out'.
*/
void Texture::render_fade( void )
{
    if( mFading )
    {
        /*  Get the alpha value */
        Uint8 a;
        SDL_GetTextureAlphaMod( mTexture, &a );

        /*  Decrease the alpha value or set it to zero */
        if( a >= 8 )
            a -= 8;
        else
            a = 0;

        /*  Apply the modified alpha to the texture */
        SDL_SetTextureAlphaMod( mTexture, a );

        /*  Create the draw rect and render the texture */
        SDL_Rect dRect = { mPos.x, mPos.y, mWidth, mHeight };
        SDL_RenderCopy( gRenderer, mTexture, NULL, &dRect );

        /*  If we've hit zero alpha, reset the texture and switch off fading */
        if( a == 0 )
        {
            mFading = false;
            SDL_SetTextureAlphaMod( mTexture, (Uint8)255 );
        }
    }
}


/*
--------------------------------------------------------------------------------
                                RENDER FLASHING
--------------------------------------------------------------------------------
 *  This method is similar to render_self() except it switches between rendering
 *  the texture and rendering nothing at quick, regular intervals.  This causes
 *  the rendered image on screen to 'flash' or 'flicker'.
*/
void Texture::render_flashing( void )
{
    /*  If we're above a certain number of ticks, render normally */
    if( mFlashTicks > mMaxFlashTicks / 2 )
    {
        render_self();
        --mFlashTicks;
    }

    /*  If we're at zero ticks, reset them to full */
    else if( mFlashTicks == 0 )
        mFlashTicks = mMaxFlashTicks;

    /*  Otherwise, decrement the ticks */
    else
        --mFlashTicks;
}




/*
--------------------------------------------------------------------------------
                               SET / GET POSITION
--------------------------------------------------------------------------------
*/
void Texture::set_position( int x, int y )
{
    /*  Set positions */
    mPos.x = x;
    mPos.y = y;

    /*  Correct X position */
    if( mPos.x < 0 )
        mPos.x = 0;
    else if( mPos.x + mWidth > WWIDTH )
        mPos.x = BWIDTH - mWidth;

    /*  Correct Y position */
    if( mPos.y < 0 )
        mPos.y = 0;
    else if( mPos.y + mHeight > WHEIGHT )
        mPos.y = WHEIGHT - mHeight;
}

int Texture::get_pos_x( void )
{
    return( mPos.x );
}

int Texture::get_pos_y( void )
{
    return( mPos.y );
}


/*
--------------------------------------------------------------------------------
                                 MODULATE ALPHA
--------------------------------------------------------------------------------
 *  This method modulates the texture's alpha value to whatever was passed.
*/
void Texture::mod_alpha( Uint8 alpha )
{
    if( mTexture != NULL )
        SDL_SetTextureAlphaMod( mTexture, alpha );
}



/*
--------------------------------------------------------------------------------
                                 INIT COLLIDERS
--------------------------------------------------------------------------------
 *  This method will generate 'colliders' for the given surface, storing them
 *  in this texture's colliders vector array.  A collider, at least as used in
 *  this game, is a rectangle 1 pixel high with variable width.  The X position
 *  is also variable, and the Y position will match the 'row' of the given
 *  clip's colliders vector.
*/
void Texture::generate_colliders( SDL_Surface *surface, int size, int frame )
{
    /*  Grab a pointer to the surface pixels */
    Uint32 *pixels = (Uint32*)surface->pixels;

    /*  These will hold the RGBA values */
    Uint8 r, g, b, a;

    /*  Variable collider rect boundaries */
    int left, right;
    int width;

    /*  Clear any colliders that might be in this frame's colliders vector */
    mColliders[ frame ].clear();

    /*  For each row of this part of the texture (clip) */
    for( int cRow = 0; cRow < size; ++cRow )
    {
        /*  Init them both to impossible values */
        left = right = -1;

        /*  For each column of this texture's clip */
        for( int cCol = 0; cCol < size; ++cCol )
        {
            /*  Increment the pixels pointer */
            ++pixels;

            /*
             *  Grab the RGBA value for the correct pixel relative to the pixel
             *  pointer's position.  To be honest, this was 90% brute-force
             *  guesswork on my part.
             */
            SDL_GetRGBA( pixels[ (size * frame * size) ],
                    surface->format, &r, &g, &b, &a );

            /*  If the alpha of the pixel isn't zero */
            if( a != 0 )
            {
                /*  If the left value has not been set to something real yet */
                if( left < 0 )
                    left = cCol;

                /*  Just keep readjusting the rightmost boundary */
                right = cCol;
            }
        }

        /*  Get the width by, what else, subtracted left from right */
        width = right - left;

        /*  If there were no visible pixels, set the width to zero */
        if( left < 0 )
            width = 0;

        /*  Create a new collider instance and fill it with data */
        Collider collider = { left, cRow, width, 1 };

        /*  Push it onto this frame's colliders vector */
        mColliders[ frame ].push_back( collider );
    }

}


/*
--------------------------------------------------------------------------------
                               GET PIXEL COLLIDER
--------------------------------------------------------------------------------
 *  This is used outside this class to return a colliders vector
*/
std::vector<Collider> Texture::get_pixel_collider( int frame )
{
    return( mColliders[ frame ] );
}


/*
--------------------------------------------------------------------------------
                                   FADE STUFF
--------------------------------------------------------------------------------
*/
void Texture::set_fading( bool fade )
{
    mFading = fade;
}

bool Texture::is_fading( void )
{
    return( mFading );
}



/*
--------------------------------------------------------------------------------
                                   GET ALPHA
--------------------------------------------------------------------------------
 *  Get the alpha value from the texture and return it
*/
Uint8 Texture::get_alpha( void )
{
    Uint8 alpha;
    SDL_GetTextureAlphaMod( mTexture, &alpha );

    return( alpha );
}



/*
--------------------------------------------------------------------------------
                                   SET ALPHA
--------------------------------------------------------------------------------
 *  Modulate the alpha value of the texture with the given alpha value
*/
void Texture::set_alpha( Uint8 alpha )
{
    Uint8 a = 0;

    /*  We don't accept values below zero or above 255 */
    if( alpha < 0 )
        a = 0;
    else if( alpha > 255 )
        a = 255;
    else
        a = alpha;

    /*  Modulate the texture's alpha value */
    SDL_SetTextureAlphaMod( mTexture, a );
}


/*
--------------------------------------------------------------------------------
                              GET / SET COLOR MOD
--------------------------------------------------------------------------------
*/
void Texture::get_color_mod( Uint8 *r, Uint8 *g, Uint8 *b )
{
    SDL_GetTextureColorMod( mTexture, r, g, b );
}

void Texture::set_color_mod( Uint8 r, Uint8 g, Uint8 b )
{
    SDL_SetTextureColorMod( mTexture, r, g, b );
}



/*
--------------------------------------------------------------------------------
                                 SAVE COLOR MOD
--------------------------------------------------------------------------------
 *  This method saves a backup of the original color mod value
*/
void Texture::save_color_mod( void )
{
    /*  Get the color mod from the texture */
    Uint8 r, g, b;
    SDL_GetTextureColorMod( mTexture, &r, &g, &b );

    /*  Create a new color from it */
    SDL_Color orig = { r, g, b, 255 };
    
    /*  Store that color */
    mOriginalColorMod = orig;
}



/*
--------------------------------------------------------------------------------
                               RESTORE COLOR MOD
--------------------------------------------------------------------------------
 *  This method restores the texture's color mod from backup
*/
void Texture::restore_color_mod( void )
{
    /*  Get the original values */
    Uint8 r = mOriginalColorMod.r;
    Uint8 g = mOriginalColorMod.g;
    Uint8 b = mOriginalColorMod.b;

    /*  Set the texture color mod to those values */
    SDL_SetTextureColorMod( mTexture, r, g, b );
}



/*
--------------------------------------------------------------------------------
                                  FLASH STUFF
--------------------------------------------------------------------------------
*/
void Texture::set_flashing( bool flashing )
{
    mFlashing = flashing;
}

bool Texture::is_flashing( void )
{
    return( mFlashing );
}

void Texture::set_flash_ticks( int ticks )
{
    mFlashTicks = ticks;
}

int Texture::get_flash_ticks( void )
{
    return( mFlashTicks );
}

void Texture::set_max_flash_ticks( int ticks )
{
    mMaxFlashTicks = ticks;
}

int Texture::get_max_flash_ticks( void )
{
    return( mMaxFlashTicks );
}

int Texture::get_max_flash_ticks_default( void )
{
    return( mMaxFlashTicksDefault );
}



/*
--------------------------------------------------------------------------------
                                  FOCUS STUFF
--------------------------------------------------------------------------------
*/
void Texture::set_focus( bool focus )
{
    mHasFocus = focus;
}


bool Texture::has_focus( void )
{
    return( mHasFocus );
}
