/*******************************************************************************
 *  kisskill.cpp
 *
 *  This file defines the methods used to add 'kiss' or 'kill' OSDs to the
 *  screen whenever the player 'kisses' or kills an asteroid.
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
KissKill::KissKill( void )
{
    clear();
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
KissKill::~KissKill( void )
{
    clear();
}



/*
--------------------------------------------------------------------------------
                                     CLEAR
--------------------------------------------------------------------------------
 *  Clears out the kk structs vector
*/
void KissKill::clear( void )
{
    mKissKills.clear();
}



/*
--------------------------------------------------------------------------------
                                      ADD
--------------------------------------------------------------------------------
 *  Adds a new kissKill struct object to the mKissKills vector
*/
bool KissKill::add( int x, int y, const char *string, SDL_Color &color )
{
    /*  Create our struct instance and set default values */
    kissKill kk;
    kk.texture = NULL;
    kk.isActive = false;

    /*  Create a texture */
    kk.texture = new Texture();
    if( ! kk.texture->create_texture_from_string( gFontTiny, string, color ) )
    {
        printf("ERROR:  Could not create kiss/kill OSD\n");
        return( false );
    }

    /*  Set the texture's position */
    kk.texture->set_position( x, y );

    /*  Switch it to active */
    kk.isActive = true;

    /*  Push it on to the vector */
    mKissKills.push_back( kk );

    return( true );
}


/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Get rid of dead kiss/kill texture objects
*/
void KissKill::update( void )
{
    /*  Create our iterator */
    std::vector<kissKill>::iterator k;

    /*  Iterate through vector, cleaning out the dead kk structs */
    for( k = mKissKills.begin(); k != mKissKills.end(); )
    {
        if( ! k->isActive )
            mKissKills.erase( k );
        else
            ++k;
    }

    /*  Create our alpha variable up here */
    Uint8 alpha = 0;

    /*  Go through the vector again, updating the active kk structs */
    for( k = mKissKills.begin(); k != mKissKills.end(); ++k )
    {
        /*  Grab the alpha from the texture */
        alpha = k->texture->get_alpha();

        /*  Modify alpha value */
        if( alpha > 16 )
            alpha -= 16;

        /*  If it's too low, set alpha to zero and deactive the kk */
        else
        {
            alpha = 0;
            k->isActive = false;
        }

        /*  Give it back to the texture */
        k->texture->set_alpha( alpha );
    }
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  Render all of our precious kk struct texture objects
*/
void KissKill::render( void )
{
    std::vector<kissKill>::iterator k;
    for( k = mKissKills.begin(); k != mKissKills.end(); ++k )
        k->texture->render_self();
}
