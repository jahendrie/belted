/*******************************************************************************
 *  util.h
 *
 *  This file declares all of the global variables, pointers, structs and enums
 *  used throughout the program.  It also includes all of the header files the
 *  program needs, including those specific to this program.
 *
*******************************************************************************/
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>              //  For printf, file IO, etc.
#include <time.h>               //  Used to seed rand
#include <vector>               //  Handy
#include <list>                 //  Also handy
#include <string>               //  I'm lazy, so sue me
#include <SDL2/SDL.h>           //  SDL stuff
#include <SDL2/SDL_image.h>     //  Image loading
#include <SDL2/SDL_mixer.h>     //  SFX / music
#include <SDL2/SDL_ttf.h>       //  Font stuff


/*
--------------------------------------------------------------------------------
                                    STRUCTS
--------------------------------------------------------------------------------
*/

/*
 *  Collider struct
 *      Used for per-pixel collision detection
 */
struct Collider
{
    int x;              //  X position
    int y;              //  Y position
    int w;              //  Width
    int h;              //  Height
    bool a;             //  Whether or not alpha in the rect has been activated
};


/*
 *  Circle struct
 *      Theoretically used for circular collision detection, though I don't
 *      think I actually use any in the game.  Still, I guess it's a good thing
 *      to have around.
 */
struct Circle
{
    int x;      //  X position
    int y;      //  Y position
    int r;      //  Radius
};


/*
 *  Transition struct
 *      Used to keep all of the information needed to conduct transitions from
 *      one screen to another.
 */
struct Transition
{
    int ticks;          //  How many ticks remain
    int maxTicks;       //  Maxiumum possible ticks
    bool started;       //  Has this transition begun?
    int velocity;       //  Velocity of transition

    int x;              //  X position of the transition
    int y;              //  Y position of the transition
    int w;              //  Width
    int h;              //  Height

    int from;           //  Which screen we're transitioning from
    int to;             //  Which screen we're transitioning to

    int direction;      //  Which direction it's moving
};


/*
 *  Record struct
 *      Used to store all of the information needed to represent a player's
 *      score.
 */
struct ScoreRecord
{
    Uint32 score;               //  Player's score
    char initials[ 4 ];         //  Player's initials
};


/*
--------------------------------------------------------------------------------
                                     ENUMS
--------------------------------------------------------------------------------
*/

/*  All of the possible screens the player can be on */
enum screens
{
    SCREEN_TRANSITION,          //  Transition rendering screen
    SCREEN_MAIN,                //  Main gameplay screen
    SCREEN_MENU,                //  Main menu
    SCREEN_GAME_OVER,           //  Game over screen
    SCREEN_HIGH_SCORES,         //  Hall of fame (high scores) screen
    SCREEN_ENTER_HIGH_SCORE,    //  Screen where the player enters their score
    SCREEN_HELP,                //  Help screen
    SCREEN_CREDITS,             //  Credits screen
    TOTAL_SCREENS
};


/*  Used for an SDL_Color array; convenient for the simple-minded like me */
enum colors
{
    COLOR_WHITE,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_VIOLET,
    COLOR_CYAN,
    COLOR_ORANGE,
    COLOR_HOT_PINK,
    COLOR_LIME,
    COLOR_BLACK,
    TOTAL_COLORS
};


/*  Easier to remember than '0 is left, 2 is up', etc. */
enum directionKeyEnum
{
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN,
    TOTAL_DIRECTIONS
};



/*
--------------------------------------------------------------------------------
                                    STRINGS
--------------------------------------------------------------------------------
*/
extern const std::string VERSION;           //  Version number string
extern const std::string DAT_FILE_PATH;     //  scores.dat file path
extern const std::string TXT_FILE_PATH;     //  scores.txt file path
extern const std::string STORY_FILE_PATH;   //  story.txt file path
extern char currentScoreString[ 10 ];       //  String for current score



/*
--------------------------------------------------------------------------------
                                VARIOUS INTEGERS
--------------------------------------------------------------------------------
*/
extern const unsigned int DEFAULT_FPS;      //  Default frames per second
extern unsigned int FPS;                    //  Current fps

extern const int DEFAULT_WINDOW_WIDTH;      //  Default window width
extern const int DEFAULT_WINDOW_HEIGHT;     //  Default window height
extern int WWIDTH;                          //  Current window width
extern int WHEIGHT;                         //  Current window height
extern int BWIDTH;                          //  Current boundary width
extern int BHEIGHT;                         //  Current boundary height

extern int currentScreen;                   //  Current screen
extern int enemyDelay;                      //  Delay before enemies start down
extern int warpSpeed;                       //  How fast the game is moving
extern int maxWarpSpeed;                    //  How fast the game can move
extern int pulseDirection;                  //  Direction (in/out) of a pulse
extern int initialsClicked;                 //  How many initials were clicked
extern Uint32 currentScore;                 //  Current player score
extern Uint32 chargeScore;                  //  Score tracker for the charge
extern Uint32 extraLifeScore;               //  Score tracker for 1ups
extern Uint32 miscTicks;                    //  Misc tick tracker

extern Uint32 gPixelFormat;                 //  Pixel format


/*
--------------------------------------------------------------------------------
                                VARIOUS BOOLEANS
--------------------------------------------------------------------------------
*/
extern bool quit;           //  Does the player want to quit?
extern bool limitFPS;       //  Do we deliberately limit the FPS?
extern bool screenFlash;    //  Are we going to flash the screen?
extern bool warp;           //  Is the player warping?
extern bool gamePaused;     //  Is the game paused?
extern bool playMusic;      //  Do we play music?
extern bool playSound;      //  Do we play sound effects?


/*
--------------------------------------------------------------------------------
                                   SDL STUFF
--------------------------------------------------------------------------------
*/
extern SDL_Window *gWindow;         //  Global window
extern SDL_Renderer *gRenderer;     //  Global renderer


/*
--------------------------------------------------------------------------------
                                     FONTS
--------------------------------------------------------------------------------
*/
extern TTF_Font *gFont;         //  Default (big) font
extern TTF_Font *gFontSmall;    //  Smaller font
extern TTF_Font *gFontTiny;     //  Smallest font


/*
--------------------------------------------------------------------------------
                                 SOUND EFFECTS
--------------------------------------------------------------------------------
*/
extern Mix_Chunk *soundEffectExtraLife;     //  Extra life sound effect
extern Mix_Chunk *soundEffectDing;          //  'Ding' sound effect
extern Mix_Chunk *soundEffectExplosion;     //  Default (player) explosion
extern Mix_Chunk *soundEffectExplosion2;    //  Alternate (asteroid) explosion
extern Mix_Chunk *soundEffectHonk;          //  Car honking sound effect
extern Mix_Chunk *soundEffectKiss;          //  Points earned by honking sfx
extern Mix_Chunk *soundEffectTick;          //  Charge meter ticking up
extern Mix_Chunk *soundEffectEngineFail;    //  Engine failing to start sfx
extern Mix_Chunk *soundEffectEngineUp;      //  Engine revving up sound effect
extern Mix_Chunk *soundEffectEngineDown;    //  Engine coming down sound effect
extern Mix_Chunk *soundEffectTransition;    //  'Whoosh' transition sound


/*
--------------------------------------------------------------------------------
                                     MUSIC
--------------------------------------------------------------------------------
*/
extern Mix_Music *musicMenu;    //  Music played when the game is first started
extern Mix_Music *musicMain;    //  Music played during normal gameplay


/*
--------------------------------------------------------------------------------
                                     COLORS
--------------------------------------------------------------------------------
*/
extern SDL_Color colors[ TOTAL_COLORS ];    //  Colors array for convenience
extern SDL_Color borderColor;               //  Default border color



/*
--------------------------------------------------------------------------------
                                   MY HEADERS
--------------------------------------------------------------------------------
*/
#ifndef CLASSES_H
#include "classes.h"        //  Headers for all the classes
#endif

#ifndef PROTOTYPES_H
#include "prototypes.h"     //  Global functions
#endif


/*
--------------------------------------------------------------------------------
                            TEXTURE OBJECT POINTERS
--------------------------------------------------------------------------------
*/
/*  --------    Unique textures     --------- */
extern Texture *playerTexture;          //  Player's ship spritesheet
extern Texture *playerWhiteTexture;     //  Player's ship (white texture)
extern Texture *enemyTexture;           //  Asteroids   spritesheet
extern Texture *panelBackground;        //  Main panel texture
extern Texture *panelButtons;           //  Panel buttons spritesheet

/*  ---------   Text textures   -------- */
extern Texture *gameOverText;           //  Game over
extern Texture *scoreText;              //  Current score text
extern Texture *highScoreText;          //  Highest score text
extern Texture *scoreQualifyText1;      //  Score qualify screen text hint 1
extern Texture *scoreQualifyText2;      //  Score qualify screen text hint 2
extern Texture *scoreQualifyText3;      //  Score qualify screen text hint 3
extern Texture *enterHighScoreText1;    //  Enter high score text hint 1
extern Texture *enterHighScoreText2;    //  Enter high score text hint 2
extern Texture *OSD;                    //  Generic OSD text texture

/*  ---------   Render target textures  ---*/
extern SDL_Texture *transTexture1;      //  Target texture for the 'from' screen
extern SDL_Texture *transTexture2;      //  Target texture for the 'to' screen


/*
--------------------------------------------------------------------------------
                            VARIOUS OBJECT POINTERS
--------------------------------------------------------------------------------
*/
extern Starfield *starfield;        //  Stars rendered in the background
extern Scores *gScores;             //  Handles all the score stuff
extern Initial *initials[ 3 ];      //  Player initials objects
extern Help *helpScreen;            //  Help screen
extern Credits *credits;            //  Credits screen
extern Menu *menuScreen;            //  Main menu screen


/*
--------------------------------------------------------------------------------
                                CLASS INSTANCES
--------------------------------------------------------------------------------
*/
extern Player player;                               //  The player
extern std::vector<Enemy> enemies;                  //  The asteroids
extern Panel panel;                                 //  The panel at the bottom
extern std::vector<AtariExplosion> aExplosions;     //  'Atari' explosions
extern Tail tail;                                   //  Tail that follows player
extern Transition transition;                       //  Global transition struct
extern KissKill kissKills;                          //  kiss/kill OSDs

#endif
