/*******************************************************************************
 *  menu.cpp
 *
 *  This defines the menu screen class.  These functions create, position,
 *  handle events for and render every element on the main menu screen.
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
Menu::Menu( void )
{
    /*  Null the graphic texture */
    mGraphic = NULL;

    /*  Null the version texture pointer */
    mVersion = NULL;

    /*  Init our selections */
    for( int i = 0; i < TOTAL_SELECTIONS; ++i )
    {
        /*  Null the textures */
        selections[ i ].textureNormal = NULL;
        selections[ i ].texturePulse = NULL;

        /*  Set the selection number */
        selections[ i ].num = i;

        /*  Set activated / pulse statuses to false */
        selections[ i ].pulse = false;
        selections[ i ].activated = false;
    }

}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Menu::~Menu( void )
{
    /*  Free the textures */
    free_textures();

    /*  Set everything else to 0 / false */
    for( int i = 0; i < TOTAL_SELECTIONS; ++i )
    {
        selections[ i ].num = 0;
        selections[ i ].pulse = false;
        selections[ i ].activated = false;
    }
}


/*
--------------------------------------------------------------------------------
                                  FREE TEXTURE
--------------------------------------------------------------------------------
 *  Frees a given texture
*/
void Menu::free_texture( Texture *texture )
{
    /*  If the texture isn't null, free it */
    if( texture != NULL )
    {
        delete texture;
        texture = NULL;
    }
}




/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
 *  Frees all relevant textures
*/
void Menu::free_textures( void )
{
    /*  Free the graphic texture */
    if( mGraphic != NULL )
        free_texture( mGraphic );

    /*  Free the version text string */
    if( mVersion != NULL )
        free_texture( mVersion );

    /*  Free all of the text selection textures */
    for( int i = 0; i < TOTAL_SELECTIONS; ++i )
    {
        free_texture( selections[ i ].textureNormal );
        free_texture( selections[ i ].texturePulse );
    }
}



/*
--------------------------------------------------------------------------------
                                CREATE TEXTURES
--------------------------------------------------------------------------------
 *  Create all of the texture objects that we'll need for the menu screen
*/
bool Menu::create_textures( void )
{
    /*  Create graphic texture object */
    mGraphic = new Texture();
    if( mGraphic == NULL )
        return( false );

    /*  Create version text texture object */
    mVersion = new Texture();
    if( mVersion == NULL )
        return( false );

    /*  For every possible selection struct, create its texture objects */
    for( int i = 0; i < TOTAL_SELECTIONS; ++i )
    {
        selections[ i ].textureNormal = new Texture();
        selections[ i ].texturePulse = new Texture();

        if( selections[ i ].textureNormal == NULL ||
                selections[ i ].texturePulse == NULL )
        {
            return( false );
        }
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                 INIT SELECTION
--------------------------------------------------------------------------------
 *  This inits a given menu selection (struct) with a given string and color
*/
bool Menu::init_selection( struct menuSelection &s, const char *string,
        SDL_Color color )
{

    /*  Load the struct's normal texture object */
    if( ! s.textureNormal->create_texture_from_string( gFont, string,
                colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not init selection %d (normal texture)\n", s.num);
        return( false );
    }

    /*  Load the struct's 'special' texture object */
    if( ! s.texturePulse->create_texture_from_string( gFont, string, color ) )
    {
        printf("ERROR:  Could not init selection %d (pulse texture\n", s.num );
        return( false );
    }

    return( true );
}




/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Initialize textures and load media
*/
bool Menu::init( void )
{
    /*  Free textures if they exist */
    free_textures();

    /*  Create the texture objects */
    if( ! create_textures() )
    {
        printf("ERROR:  Could not create texture objects\n");
        return( false );
    }

    /*  Init the graphic */
    if( ! mGraphic->create_texture_from_file( "data/gfx/menu-graphic.png" ) )
    {
        printf("ERROR:  Could not init menu graphic texture\n");
        return( false );
    }

    /*  Init the version texture */
    if( ! mVersion->create_texture_from_string( gFontTiny, VERSION.c_str(),
                colors[ COLOR_WHITE ] ) )
    {
        return( false );
    }

    /*  Init start selection */
    if( ! init_selection( selections[ SELECTION_START ], "START GAME",
                colors[ COLOR_GREEN ] ) )
    {
        return( false );
    }

    /*  Init resume selection */
    if( ! init_selection( selections[ SELECTION_RESUME ], "RESUME GAME",
                colors[ COLOR_YELLOW ] ) )
    {
        return( false );
    }

    /*  Init hall of fame selection */
    if( ! init_selection( selections[ SELECTION_HOF ], "VIEW HIGH SCORES",
                colors[ COLOR_CYAN ] ) )
    {
        return( false );
    }

    /*  Init help selection */
    if( ! init_selection( selections[ SELECTION_HELP ], "HELP",
                colors[ COLOR_CYAN ] ) )
    {
        return( false );
    }

    /*  Init credits selection */
    if( ! init_selection( selections[ SELECTION_CREDITS ], "CREDITS",
                colors[ COLOR_CYAN ] ) )
    {
        return( false );
    }

    /*  Init quit selection */
    if( ! init_selection( selections[ SELECTION_QUIT ], "QUIT",
                colors[ COLOR_RED ] ) )
    {
        return( false );
    }


    /*  Set the first item to activated status */
    selections[ SELECTION_RESUME ].activated = true;


    /*  Position textures */
    this->layout();

    /*  If we're good */
    return( true );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
 *  Position all of the texture objects
*/
void Menu::layout( void )
{
    /*  Set the position for the graphic on the screen */
    mGraphic->set_position( 0, 80 );

    /*  Set the position of the version number */
    mVersion->set_position(
            ( mGraphic->get_pos_x() + mGraphic->get_width() ) -
            mVersion->get_width(),
            ( mGraphic->get_pos_y() + mGraphic->get_height() ) -
            mVersion->get_height() );

    /*  This makes positioning the selections easier (relative positioning) */
    int y = mGraphic->get_pos_y() + mGraphic->get_height() + 60;


    /*  'start' and 'resume' have the same position */
    for( int i = SELECTION_START; i <= SELECTION_RESUME; ++i )
    {
        selections[ i ].textureNormal->set_position(
                ( BWIDTH - selections[ i ].textureNormal->get_width() ) / 2, y);
        selections[ i ].texturePulse->set_position(
                ( BWIDTH - selections[ i ].texturePulse->get_width() ) / 2, y );
    }


    /*  Position the rest of the textures farther down */
    for( int i = SELECTION_HOF; i < TOTAL_SELECTIONS; ++i )
    {
        selections[ i ].textureNormal->set_position(
                ( BWIDTH - selections[ i ].textureNormal->get_width() ) / 2,
                y + ( i * 40 ) );
        selections[ i ].texturePulse->set_position(
                ( BWIDTH - selections[ i ].texturePulse->get_width() ) / 2,
                y + ( i * 40 ) );
    }
}




/*
--------------------------------------------------------------------------------
                                     SELECT
--------------------------------------------------------------------------------
 *  Handles what happens when a given selection has been 'entered'
*/
void Menu::select( int currentSelection )
{
    switch( currentSelection )
    {
        /*  Player chooses to resume the game */
        case SELECTION_RESUME:
            if( gamePaused )
            {
                start_transition( SCREEN_MAIN, DIRECTION_UP );

                if( Mix_PausedMusic() == 1 )
                    Mix_ResumeMusic();
            }
            else
            {
                reset();
                start_transition( SCREEN_MAIN, DIRECTION_UP );
            }
            break;

        /*  Player chooses to view the hall of fame (high scores) */
        case SELECTION_HOF:
            start_transition( SCREEN_HIGH_SCORES, DIRECTION_LEFT );
            break;

        /*  Player chooses to view the help screen */
        case SELECTION_HELP:
            start_transition( SCREEN_HELP, DIRECTION_DOWN );
            break;

        /*  Player chooses to view the credits screen */
        case SELECTION_CREDITS:
            start_transition( SCREEN_CREDITS, DIRECTION_RIGHT );
            break;

        /*  Player chooses to quit the game */
        case SELECTION_QUIT:
            quit = true;
            break;
    }
}



/*
--------------------------------------------------------------------------------
                                 HANDLE EVENTS
--------------------------------------------------------------------------------
 *  Master event handler for the menu screen
*/
void Menu::handle_events( SDL_Event &e )
{
    /*  Find the current selection */
    int currentSelection = 0;
    for( int i = 0; i < TOTAL_SELECTIONS; ++i )
    {
        if( selections[ i ].activated )
            currentSelection = selections[ i ].num;
    }

    /*  If they clicked a mouse button */
    if( e.type == SDL_MOUSEBUTTONUP )
    {
        /*  Middle button always toggles paused / unpaused */
        if( e.button.button == SDL_BUTTON_MIDDLE )
            select( SELECTION_RESUME );

        /*  Otherwise, click whatever they selected */
        else
            select( currentSelection );
    }

    /*  If they used the mouse wheel */
    if( e.type == SDL_MOUSEWHEEL )
    {
        if( e.wheel.y > 0 )
            --currentSelection;
        else if( e.wheel.y < 0 )
            ++currentSelection;
    }


    /*  If they pushed a key */
    if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_ESCAPE:                   //  ESCAPE KEY
                if( gamePaused )
                    start_transition( SCREEN_MAIN, DIRECTION_UP );
                else
                    quit = true;
                break;

            case SDLK_q:        quit = true;                    break;
            case SDLK_s:        toggle_sounds();                break;
            case SDLK_m:        toggle_music();                 break;
            case SDLK_UP:       --currentSelection;             break;
            case SDLK_DOWN:     ++currentSelection;             break;
            case SDLK_RETURN:   select( currentSelection );     break;
            case SDLK_SPACE:    select( currentSelection );     break;
        }
    }

    /*  Set the activated / pulse status for the selections */
    for( int i = 0; i < TOTAL_SELECTIONS; ++i )
    {
        selections[ i ].activated = false;
        selections[ i ].pulse = false;
    }

    /*  Correct the selection */
    if( currentSelection > SELECTION_QUIT )
        currentSelection = SELECTION_RESUME;
    else if( currentSelection < SELECTION_RESUME )
        currentSelection = SELECTION_QUIT;

    /*  Start and resume are in the same spot */
    if( currentSelection == SELECTION_START ||
            currentSelection == SELECTION_RESUME )
    {
        /*  Set them both to true and pulsing */
        selections[ SELECTION_START ].activated = true;
        selections[ SELECTION_START ].pulse = true;
        selections[ SELECTION_RESUME ].activated = true;
        selections[ SELECTION_RESUME ].pulse = true;

        /*  Now just set start to resume */
        if( currentSelection == SELECTION_START )
            currentSelection = SELECTION_RESUME;
    }

    /*  If anything else was selected */
    else
    {
        /*  Go through the rest of the selection */
        for( int i = SELECTION_HOF; i < TOTAL_SELECTIONS; ++i )
        {
            /*  If the current selection was the the one selected */
            if( currentSelection == selections[ i ].num )
            {
                /*  Set it to true and pulsing */
                selections[ i ].activated = true;
                selections[ i ].pulse = true;
            }

            /*  Otherwise */
            else
            {
                /*  Set it to false and not pulsing */
                selections[ i ].activated = false;
                selections[ i ].pulse = false;
            }
        }
    }


}



/*
--------------------------------------------------------------------------------
                                RENDER SELECTION
--------------------------------------------------------------------------------
 *  Render the current selection text texture
*/
void Menu::render_selection( struct menuSelection &s )
{
    /*  If it's pulsing, render it as such */
    if( s.pulse )
        render_pulse( s.textureNormal, s.texturePulse, 16 );

    /*  Otherwise, render it normally */
    else
        s.textureNormal->render_self();
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  Render everything
*/
void Menu::render( void )
{
    /*  Render the graphic */
    mGraphic->render_self();

    /*  Render the version number texture */
    mVersion->render_self();

    /*  Render a line both above and below the graphic */
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );

    /*  First line */
    SDL_RenderDrawLine( gRenderer,
            mGraphic->get_pos_x(), mGraphic->get_pos_y(),
            (mGraphic->get_pos_x() + mGraphic->get_width()),
            mGraphic->get_pos_y() );

    /*  Second line */
    SDL_RenderDrawLine( gRenderer,
            mGraphic->get_pos_x(),
            ( mGraphic->get_pos_y() + mGraphic->get_height() ),
            ( mGraphic->get_pos_x() + mGraphic->get_width() ),
            ( mGraphic->get_pos_y() + mGraphic->get_height() ) );

    /*  If we're paused, render 'resume text'; otherwise, render 'start game' */
    if( gamePaused )
        render_selection( selections[ SELECTION_RESUME ] );
    else
        render_selection( selections[ SELECTION_START ] );

    /*  Render the rest of them */
    for( int i = SELECTION_HOF; i < TOTAL_SELECTIONS; ++i )
        render_selection( selections[ i ] );
}
