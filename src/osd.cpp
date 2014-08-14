/*******************************************************************************
 *  osd.cpp
 *
 *  This file defines all of the OSD-specific functions that one might need
 *  when displaying a simple on-screen text 'hint' for a second or two.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                    FREE OSD
--------------------------------------------------------------------------------
 *  Deletes the OSD texture and nulls the pointer
*/
void free_osd( void )
{
    if( OSD != NULL )
    {
        delete OSD;
        OSD = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                      OSD
--------------------------------------------------------------------------------
 *  Inits the OSD according to the given string
*/
void osd( const char *string )
{
    /*  Free old OSD texture object if it exists */
    free_osd();

    /*  Create a brand new one */
    OSD = new Texture();

    /*  Load the string into it */
    if( ! OSD->create_texture_from_string( gFont, string, colors[COLOR_WHITE]) )
    {
        printf("WARNING:  Could not create OSD!\n");
    }

    /*  Position the OSD at the top-center of the screen */
    OSD->set_position( ( BWIDTH - OSD->get_width() ) / 2, 40 );
}



/*
--------------------------------------------------------------------------------
                                   UPDATE OSD
--------------------------------------------------------------------------------
 *  Updates the OSD, which in effect just makes it visually fade away over time.
*/
void update_osd( void )
{
    /*  If the OSD exists */
    if( OSD != NULL )
    {
        /*  Get the alpha value from the texture object */
        Uint8 alpha = OSD->get_alpha();

        /*  If the value is higher than 8, lower it */
        if( alpha > 8 )
            OSD->set_alpha( alpha - 8 );

        /*  Otherwise, we're done with this OSD instance */
        else
            free_osd();
    }
}



/*
--------------------------------------------------------------------------------
                                   RENDER OSD
--------------------------------------------------------------------------------
 *  Renders the OSD to the screen
*/
void render_osd( void )
{
    /*  If the OSD exists, render it */
    if( OSD != NULL )
        OSD->render_self();
}
