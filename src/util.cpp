/*******************************************************************************
 *  util.cpp
 *
 *  This file defines all the global variables and assigns values to various
 *  pointers.  These are all declared in util.h.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                      FPS
--------------------------------------------------------------------------------
*/
const unsigned int DEFAULT_FPS = 60;    //  Default FPS
unsigned int FPS = DEFAULT_FPS;


/*
--------------------------------------------------------------------------------
                                    STRINGS
--------------------------------------------------------------------------------
*/
const std::string VERSION = "0.92";                     //  Version string
const std::string DAT_FILE_PATH = "data/scores.dat";    //  Scores file
const std::string TXT_FILE_PATH = "data/scores.txt";    //  Scores txt file
const std::string STORY_FILE_PATH = "data/story.txt";   //  Story file
char currentScoreString[ 10 ];                          //  Current score string


/*
--------------------------------------------------------------------------------
                      WINDOW AND PLAY BOUNDARY DIMENSIONS
--------------------------------------------------------------------------------
*/
const int DEFAULT_WINDOW_WIDTH = 800;       //  Window created has this width
const int DEFAULT_WINDOW_HEIGHT = 800;      //  Window created has this height
int WWIDTH = DEFAULT_WINDOW_WIDTH;          //  Modifiable version of width
int WHEIGHT = DEFAULT_WINDOW_HEIGHT;        //  Modifiable version of height
int BWIDTH = WWIDTH;                        //  Play boundary width
int BHEIGHT = WHEIGHT;                      //  Play boundary height


/*
--------------------------------------------------------------------------------
                                VARIOUS INTEGERS
--------------------------------------------------------------------------------
*/
int currentScreen = SCREEN_MENU;    //  Set to the menu screen by default
int enemyDelay = 0;                 //  Delay before we start spawning enemies
int warpSpeed = 1;                  //  Speed at which the player travels
int maxWarpSpeed = 1;               //  Max warp speed; modified later
int pulseDirection = 1;             //  Positive 'pulse render' direction
int initialsClicked = 0;            //  How many initials have been clicked
Uint32 currentScore = 0;            //  Current score
Uint32 chargeScore = 0;             //  Score tracker for the charge meter
Uint32 extraLifeScore = 0;          //  Score tracker for earning an extra life
Uint32 miscTicks = 0;               //  Random ticks tracker
Uint32 gPixelFormat = 0;            //  Surface pixel format



/*
--------------------------------------------------------------------------------
                                   SDL STUFF
--------------------------------------------------------------------------------
*/
SDL_Window *gWindow = NULL;         //  Our global window
SDL_Renderer *gRenderer = NULL;     //  Our global renderer


/*
--------------------------------------------------------------------------------
                                     FONTS
--------------------------------------------------------------------------------
*/
TTF_Font *gFont = NULL;             //  Default (big) font
TTF_Font *gFontSmall = NULL;        //  Smaller font
TTF_Font *gFontTiny = NULL;         //  Smallest font


/*
--------------------------------------------------------------------------------
                                 SOUND EFFECTS
--------------------------------------------------------------------------------
*/
Mix_Chunk *soundEffectExtraLife = NULL;     //  Extra life sound effect
Mix_Chunk *soundEffectDing = NULL;          //  'Ding' sound effect
Mix_Chunk *soundEffectExplosion = NULL;     //  Default explosion
Mix_Chunk *soundEffectExplosion2 = NULL;    //  Enemy explosion
Mix_Chunk *soundEffectHonk = NULL;          //  Honk sound effect
Mix_Chunk *soundEffectKiss = NULL;          //  Points earned from honk sfx
Mix_Chunk *soundEffectTick = NULL;          //  Charge meter ticking up
Mix_Chunk *soundEffectEngineFail = NULL;    //  Engine fails to power up
Mix_Chunk *soundEffectEngineUp = NULL;      //  Engine as it revs up
Mix_Chunk *soundEffectEngineDown = NULL;    //  Engine as it revs down
Mix_Chunk *soundEffectTransition = NULL;    //  'Whoosh' transition sound


/*
--------------------------------------------------------------------------------
                                     MUSIC
--------------------------------------------------------------------------------
*/
Mix_Music *musicMenu = NULL;    //  Music played when the game is first started
Mix_Music *musicMain = NULL;    //  Music played during main gameplay


/*
--------------------------------------------------------------------------------
                                     COLORS
--------------------------------------------------------------------------------
*/
SDL_Color colors[ TOTAL_COLORS ];                   //  Our global colors array
SDL_Color borderColor = { 255, 255, 255, 255 };     //  Default border color



/*
--------------------------------------------------------------------------------
                                VARIOUS BOOLEANS
--------------------------------------------------------------------------------
*/
bool quit = false;              //  Has the player quit?
bool limitFPS = false;          //  Do we limit fps?
bool screenFlash = false;       //  Are we flashing the screen?
bool warp = false;              //  Is the player currently warping up?
bool gamePaused = false;        //  Is the game paused?
bool playMusic = true;          //  Do we play music?
bool playSound = true;          //  Do we play sound effects?


/*
--------------------------------------------------------------------------------
                            TEXTURE OBJECT POINTERS
--------------------------------------------------------------------------------
*/

/* ------------ Special textures    --------------- */
Texture *playerTexture = NULL;          //  Player's ship texture
Texture *playerWhiteTexture = NULL;     //  Player's ship texture (white)
Texture *enemyTexture = NULL;           //  Asteroids texture
Texture *panelBackground = NULL;        //  Main panel texture
Texture *panelButtons = NULL;           //  Panel buttons texture


/*  ----------  Text textures   ---------------*/
Texture *gameOverText = NULL;           //  Game over
Texture *scoreText = NULL;              //  Current score
Texture *highScoreText = NULL;          //  Highest score
Texture *scoreQualifyText1 = NULL;      //  Score screen text hint 1
Texture *scoreQualifyText2 = NULL;      //  Score screen text hint 2
Texture *scoreQualifyText3 = NULL;      //  Score screen text hint 3
Texture *enterHighScoreText1 = NULL;    //  Enter high score screen text hint 1
Texture *enterHighScoreText2 = NULL;    //  Enter high score screen text hint 2
Texture *OSD = NULL;                    //  Generic OSD text texture


/*  ---------   Target textures ------------- */
SDL_Texture *transTexture1 = NULL;      //  Target ('from') transition texture
SDL_Texture *transTexture2 = NULL;      //  Target ('to') transition texture



/*
--------------------------------------------------------------------------------
                            VARIOUS OBJECT POINTERS
--------------------------------------------------------------------------------
*/
Starfield *starfield = NULL;    //  Starfield in the background
Scores *gScores = NULL;         //  Scores object; handles all the scores stuff
Initial *initials[ 3 ];         //  Player initials when entering high score
Help *helpScreen = NULL;        //  Help screen
Credits *credits = NULL;        //  Credits screen
Menu *menuScreen = NULL;        //  Main menu screen


/*
--------------------------------------------------------------------------------
                                CLASS INSTANCES
--------------------------------------------------------------------------------
*/
Player player;                              //  The player
Panel panel;                                //  The panel
std::vector<Enemy> enemies;                 //  The asteroids
std::vector<AtariExplosion> aExplosions;    //  'Atari' explosions
Tail tail;                                  //  Tail displayed behind player
Transition transition;                      //  Transition struct instance
KissKill kissKills;                         //  Kiss/kill OSDs
