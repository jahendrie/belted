/*******************************************************************************
 *  close.cpp
 *
 *  This file defines the close function, which deletes objects, nulls pointers
 *  and otherwise frees memory that was being used by the program.  It also
 *  quits out SDL and its subsystems.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                     CLOSE
--------------------------------------------------------------------------------
 *  Close everything
*/
void close( void )
{
    /*  Get rid of the window and renderer */
    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    gWindow = NULL;
    gRenderer = NULL;

    /*  Get rid of enemy / player textures */
    delete playerTexture;
    delete playerWhiteTexture;
    delete enemyTexture;
    playerTexture = NULL;
    playerWhiteTexture = NULL;
    enemyTexture = NULL;


    /*  Get rid of text textures */
    delete gameOverText;
    delete scoreText;
    delete highScoreText;
    delete scoreQualifyText1;
    delete scoreQualifyText2;
    delete scoreQualifyText3;
    delete enterHighScoreText1;
    delete enterHighScoreText2;
    gameOverText = NULL;
    scoreText = NULL;
    highScoreText = NULL;
    scoreQualifyText1 = NULL;
    scoreQualifyText2 = NULL;
    scoreQualifyText3 = NULL;
    enterHighScoreText1 = NULL;
    enterHighScoreText2 = NULL;

    /*  Get rid of misc textures */
    delete panelBackground;
    delete panelButtons;
    panelBackground = NULL;
    panelButtons = NULL;

    /*  Get rid of the special target textures used for transitions */
    SDL_DestroyTexture( transTexture1 );
    SDL_DestroyTexture( transTexture2 );
    transTexture1 = NULL;
    transTexture2 = NULL;

    /*  Get rid of various global objects */
    delete menuScreen;
    delete gScores;
    delete helpScreen;
    delete credits;
    menuScreen = NULL;
    gScores = NULL;
    helpScreen = NULL;
    credits = NULL;

    /*  Get rid of the initials */
    for( int i = 0; i < 3; ++i )
    {
        delete initials[ i ];
        initials[ i ] = NULL;
    }

    /*  If there are any kiss/kill structs left, get rid of them */
    kissKills.clear();

    /*  Close out the fonts */
    TTF_CloseFont( gFont );
    TTF_CloseFont( gFontSmall );
    TTF_CloseFont( gFontTiny );
    gFont = NULL;
    gFontSmall = NULL;
    gFontTiny = NULL;

    /*  Free all of the sounds */
    if( Mix_Playing( -1 ) > 0 )
        Mix_HaltChannel( -1 );
    Mix_FreeChunk( soundEffectExtraLife );
    Mix_FreeChunk( soundEffectDing );
    Mix_FreeChunk( soundEffectExplosion );
    Mix_FreeChunk( soundEffectExplosion2 );
    Mix_FreeChunk( soundEffectHonk );
    Mix_FreeChunk( soundEffectKiss );
    Mix_FreeChunk( soundEffectTick );
    Mix_FreeChunk( soundEffectEngineFail );
    Mix_FreeChunk( soundEffectEngineUp );
    Mix_FreeChunk( soundEffectEngineDown );
    Mix_FreeChunk( soundEffectTransition );
    soundEffectExtraLife = NULL;
    soundEffectDing = NULL;
    soundEffectExplosion = NULL;
    soundEffectExplosion2 = NULL;
    soundEffectHonk = NULL;
    soundEffectKiss = NULL;
    soundEffectTick = NULL;
    soundEffectEngineFail = NULL;
    soundEffectEngineUp = NULL;
    soundEffectEngineDown = NULL;
    soundEffectTransition = NULL;

    /*  Free the music */
    if( Mix_PlayingMusic() == 1 )
        Mix_HaltMusic();
    Mix_FreeMusic( musicMenu );
    Mix_FreeMusic( musicMain );
    musicMenu = NULL;
    musicMain = NULL;

    /*  Get rid of the enemies */
    enemies.clear();


    /*  Close out SDL and its subsystems */
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
