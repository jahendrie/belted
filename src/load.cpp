/*******************************************************************************
 *  load.cpp
 *
 *  This file defines the various media loading (and texture creation) functions
 *  that the game uses, not including those that exist inside of various classes
 *  that are otherwise used for this sort of thing.
 *
 *  It also defines the functions for the creation and loading of said other
 *  classes.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                             CREATE BLANK TEXTURES
--------------------------------------------------------------------------------
 *  This function creates the blank target textures used by the game to render
 *  various screens onto during transitioning from one screen to another,
 *  creating a (more or less) smooth visual movement between screens.
*/
bool create_blank_textures( void )
{
    /*  Create the first blank texture */
    transTexture1 = SDL_CreateTexture( gRenderer, gPixelFormat,
            SDL_TEXTUREACCESS_TARGET, WWIDTH, WHEIGHT );

    /*  Create the second blank texture */
    transTexture2 = SDL_CreateTexture( gRenderer, gPixelFormat,
            SDL_TEXTUREACCESS_TARGET, WWIDTH, WHEIGHT );

    /*  If both textures aren't null, we're good */
    return( ( transTexture1 != NULL ) && ( transTexture2 != NULL ) );
}



/*
--------------------------------------------------------------------------------
                                   LOAD TEXT
--------------------------------------------------------------------------------
 *  This function creates and loads all of the text textures used in the game
 *  that aren't created/loaded inside of specific classes, such as those in the
 *  help screen class or those in the credits screen class.
*/
bool load_text( void )
{
    /*  Default text color is white */
    SDL_Color textColor = colors[ COLOR_WHITE ];


    /*  Game over text */
    gameOverText = new Texture();
    if( ! gameOverText->create_texture_from_string( gFont, "GAME OVER",
                textColor ) )
    {
        printf("ERROR:  Could not load game over texture.\n");
        return( false );
    }

    /*  Score display */
    scoreText = new Texture();
    if( ! scoreText->create_texture_from_string( gFontTiny, "000000",
                textColor ) )
    {
        printf("ERROR:  Could not load score text texture.\n");
        return( false );
    }

    /*  High score display */
    highScoreText = new Texture();
    if( ! highScoreText->create_texture_from_string( gFontTiny, "000000",
                textColor ) )
    {
        printf("ERROR:  Could not load high score text texture.\n");
        return( false );
    }



    return( true );
}




/*
--------------------------------------------------------------------------------
                                  LOAD SOUNDS
--------------------------------------------------------------------------------
 *  Load all of the sound effects used in the game
*/
bool load_sounds( void )
{
    /*  Extra life sound effect */
    soundEffectExtraLife = Mix_LoadWAV( "data/sfx/sound_1up.ogg" );
    if( soundEffectExtraLife == NULL )
    {
        printf("ERROR:  Could not load extra life sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Charge meter 'ding' sound effect */
    soundEffectDing = Mix_LoadWAV( "data/sfx/sound_ding.ogg" );
    if( soundEffectDing == NULL )
    {
        printf("ERROR:  Could not load ding sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Player's ship explosion sound effect */
    soundEffectExplosion = Mix_LoadWAV( "data/sfx/sound_explosion.ogg" );
    if( soundEffectExplosion == NULL )
    {
        printf("ERROR:  Could not load explosion sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Asteroid explosion sound effect */
    soundEffectExplosion2 = Mix_LoadWAV( "data/sfx/sound_explosion2.ogg" );
    if( soundEffectExplosion2 == NULL )
    {
        printf("ERROR:  Could not load explosion (2) sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Honk sound effect */
    soundEffectHonk = Mix_LoadWAV( "data/sfx/sound_honk.ogg" );
    if( soundEffectHonk == NULL )
    {
        printf("ERROR:  Could not load honk sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  The 'kiss' sound effect */
    soundEffectKiss = Mix_LoadWAV( "data/sfx/sound_kiss.ogg" );
    if( soundEffectKiss == NULL )
    {
        printf("ERROR:  Could not load kiss sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Charge meter tick sound effect */
    soundEffectTick = Mix_LoadWAV( "data/sfx/sound_tick.ogg" );
    if( soundEffectTick == NULL )
    {
        printf("ERROR:  Could not load tick sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Engine failure sound effect */
    soundEffectEngineFail = Mix_LoadWAV( "data/sfx/sound_engine-fail.ogg" );
    if( soundEffectEngineFail == NULL )
    {
        printf("ERROR:  Could not load the engine fail sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Space-engine climbing RPMs sound effect */
    soundEffectEngineUp = Mix_LoadWAV( "data/sfx/sound_engine-up.ogg" );
    if( soundEffectEngineUp == NULL )
    {
        printf("ERROR:  Could not load the engine up sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Space engine coming down sound effect */
    soundEffectEngineDown = Mix_LoadWAV( "data/sfx/sound_engine-down.ogg" );
    if( soundEffectEngineDown == NULL )
    {
        printf("ERROR:  Could not load the engine down sound effect.  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  'woosh' sound effect during transitions */
    soundEffectTransition = Mix_LoadWAV( "data/sfx/transition.ogg" );
    if( soundEffectTransition == NULL )
    {
        printf("ERROR:  Could not load transition sound effect\n");
        return( false );
    }


    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD MUSIC
--------------------------------------------------------------------------------
 *  Load all of the music used in the game
*/
bool load_music( void )
{
    /*  Load menu theme */
    musicMenu = Mix_LoadMUS( "data/music/club-diver.ogg" );
    if( musicMenu == NULL )
    {
        printf("ERROR:  Could not load menu theme club-diver.ogg\n");
        return( false );
    }

    /*  Load main theme */
    musicMain = Mix_LoadMUS( "data/music/cut-and-run.ogg" );
    if( musicMain == NULL )
    {
        printf("ERROR:  Could not load main theme cut-and-run.ogg\n");
        return( false );
    }


    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD MEDIA
--------------------------------------------------------------------------------
 *  Master media loading function.  This directly loads the loading of most
 *  unique textures used on the 'main screen' during play, while calling the
 *  other media loading functions to load those as well.
*/
bool load_media( void )
{
    /*  Player's normal texture (sprite sheet) */
    playerTexture = new Texture();
    if( ! playerTexture->create_texture_from_file("data/gfx/ship.png", true,
                77, 77, 30 ) )
    {
        printf("ERROR:  Could not load player texture\n");
        return( false );
    }

    /*  Player's white (powered) texture (sprite sheet) */
    playerWhiteTexture = new Texture();
    if( ! playerWhiteTexture->create_texture_from_file(
                "data/gfx/ship-white.png", true, 77, 77, 30 ) )
    {
        printf("ERROR:  Could not load white player texture\n");
        return( false );
    }

    /*  Enemy texture (sprite sheet) */
    enemyTexture = new Texture();
    if( ! enemyTexture->create_texture_from_file("data/gfx/asteroids.png",
                true, 99, 99, 12 ) )
    {
        printf("ERROR:  Could not load enemy texture.\n");
        return( false );
    }

    /*  Panel background texture */
    panelBackground = new Texture();
    if( ! panelBackground->create_texture_from_file(
                "data/gfx/panel-bg.png" ) )
    {
        printf("ERROR:  Could not load panel background texture.\n");
        return( false );
    }

    /*  Panel buttons texture (sprite sheet) */
    panelButtons = new Texture();
    if( ! panelButtons->create_texture_from_file(
                "data/gfx/panel-buttons.png" ) )
    {
        printf("ERROR:  Could not load panel buttons texture.\n");
        return( false );
    }

    /*  Load all sound effects */
    if( ! load_sounds() )
    {
        printf("ERROR:  Could not load sound effects\n");
        return( false );
    }

    /*  Load all music */
    if( ! load_music() )
    {
        printf("ERROR:  Could not load music\n");
        return( false );
    }

    /*  If sound and music have been disable by the user, mute it all */
    if( ! playMusic && ! playSound )
        mute( true );

    /*  Load misc text */
    if( ! load_text() )
        return( false );

    /*  Create blank 'target' transition textures */
    if( ! create_blank_textures() )
    {
        printf("ERROR:  Could not create blank target texture:  %s\n",
                SDL_GetError() );
        return( false );
    }

    /*  If the media's been loaded, wicked awesome */
    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD FONTS
--------------------------------------------------------------------------------
 *  Load all the fonts we use in the game
*/
bool load_fonts( void )
{
    /*  Load default font */
    gFont = TTF_OpenFont("data/fonts/ARCADE_N.TTF", 32 );
    if( gFont == NULL )
    {
        printf("ERROR:  Could not open font.  TTF Error:  %s\n",
                TTF_GetError() );
        return( false );
    }

    /*  Same, but a bit smaller */
    gFontSmall = TTF_OpenFont( "data/fonts/ARCADE_N.TTF", 24 );
    if( gFontSmall == NULL )
    {
        printf("ERROR:  Could not open font.  TTF Error:  %s\n",
                TTF_GetError() );
        return( false );
    }

    /*  Same, but way smaller */
    gFontTiny = TTF_OpenFont( "data/fonts/ARCADE_N.TTF", 16 );
    if( gFontTiny == NULL )
    {
        printf("ERROR:  Could not open font.  TTF Error:  %s\n",
                TTF_GetError() );
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                  LOAD PLAYER
--------------------------------------------------------------------------------
 *  Initialize and adjust player object
*/
void load_player( void )
{
    /*  Init the player object */
    player.init_player();

    /*  Set the player's texture */
    player.set_texture_object( playerTexture );
    player.set_special_texture_object( playerWhiteTexture );

    /*  Set frame info */
    player.set_max_frames( 30 );
    player.set_current_frame( 14 );

    /*  Get the player's ship texture's width */
    int w = player.get_texture_width();

    /*  Init player clips - rows, columns, width, height */
    player.init_clips_vertical( w, w, 30 );

    /*  Init width and height (scale player ship) */
    player.set_width( w );
    player.set_height( w );

    /*  Set initial position */
    player.set_position(
            ( BWIDTH - player.get_width() ) / 2,
            ( BHEIGHT - player.get_height() ) - 10 );

    /*  Adjust the colliders for the player's ship */
    player.translate_colliders( 1 );
}



/*
--------------------------------------------------------------------------------
                                   LOAD ENEMY
--------------------------------------------------------------------------------
 *  Create, init and adjust enemy object
*/
void load_enemy( void )
{
    /*  Create new enemy object */
    Enemy enemy;

    /*  Init some more variables */
    enemy.init_enemy();

    /*  Set its texture object */
    enemy.set_texture_object( enemyTexture );

    /*  Create semi-random scale size and speed */
    int scaleSize = ( rand() % 2 ) + 1;
    int speed = ( (rand()%6) + 1 ) * 2;

    /*  Init the point values */
    enemy.init_point_values( scaleSize, speed );

    /*  Adjust the dimensions according to random size */
    int w = enemy.get_texture_width();
    enemy.set_width( w / scaleSize );
    enemy.set_height( w / scaleSize );

    /*  Set position:  random X position, Y pos = 'above' visible play area */
    enemy.set_position( ( (rand() % BWIDTH) + 1), -(enemy.get_height()*2) );

    /*  Set the enemy's velocity to random speed */
    enemy.set_velocity( speed );

    /*  Set the enemy's direction downward */
    enemy.set_direction( 1 );

    /*  Set frame info */
    enemy.set_max_frames( 12 );

    /*  Randomly select one of the 12 'clips' */
    enemy.set_current_frame( rand() % 12 );

    /*  Init clips - rows, columns, width, height */
    enemy.init_clips_vertical( w, w, 12 );

    /*  Translate colliders */
    enemy.translate_colliders( scaleSize );

    /*  Push the new enemy onto the enemies vector */
    enemies.push_back( enemy );
}



/*
--------------------------------------------------------------------------------
                                   LOAD PANEL
--------------------------------------------------------------------------------
 *  Init various panel attributes
*/
void load_panel( void )
{
    /*  Assign all of the texture objects to the panel */
    panel.set_panel_texture_background( panelBackground );
    panel.set_panel_texture_buttons( panelButtons );
    panel.set_score_texture_object( scoreText );
    panel.set_high_score_texture_object( highScoreText );

    /*  Adjust panel dimensions */
    panel.set_width( BWIDTH );
    panel.set_height( 100 );
    
    /*  Adjust the positions of the panel and everything on it */
    panel.set_position( 0, BHEIGHT );
    panel.layout();
}



/*
--------------------------------------------------------------------------------
                                LOAD STARTFIELD
--------------------------------------------------------------------------------
 *  This function just creates a new startfield object and points the starfield
 *  pointer at it.
*/
void load_starfield( void )
{
    starfield = new Starfield();
}



/*
--------------------------------------------------------------------------------
                                  LOAD SCORES
--------------------------------------------------------------------------------
 *  Create the scores object (which also includes the high scores screen)
*/
bool load_scores( void )
{
    /*  Create the object */
    gScores = new Scores();
    
    /*  Init the object, or return failure if that doesn't work */
    if( ! gScores->init() )
    {
        printf("ERROR:  Could not init scores\n");
        return( false );
    }

    /*  Return success if we're good */
    return( true );
}



/*
--------------------------------------------------------------------------------
                                 LOAD INITIALS
--------------------------------------------------------------------------------
 *  Create and load all three of the initials objects
*/
bool load_initials( void )
{
    /*  Go through all three, create and load them all */
    for( int i = 0; i < 3; ++i )
    {
        initials[ i ] = new Initial();

        if( ! initials[ i ]->init() )
            return( false );
    }

    /*  Return true if it worked */
    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD HELP
--------------------------------------------------------------------------------
 *  Create and load the help screen object
*/
bool load_help( void )
{
    helpScreen = new Help();
    
    if( ! helpScreen->init() )
    {
        printf("ERROR:  Could not load help screen\n");
        return( false );
    }

    return( true );
}




/*
--------------------------------------------------------------------------------
                                  LOAD CREDITS
--------------------------------------------------------------------------------
 *  Create and load the credits screen object
*/
bool load_credits( void )
{
    credits = new Credits();
    
    if( ! credits->init() )
    {
        printf("ERROR:  Could not load credits screen\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD MENU
--------------------------------------------------------------------------------
 *  Create and load the 'main menu' screen object
*/
bool load_menu( void )
{
    menuScreen = new Menu();

    if( ! menuScreen->init() )
    {
        return( false );
    }

    return( true );
}
