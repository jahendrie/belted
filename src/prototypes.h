/*******************************************************************************
 *  prototypes.h
 *
 *  This header file is where I throw the prototypes of all the functions I want
 *  global access to.
 *
 *  Also... isn't that a weird term for this sort of thing?  "Global"?  There
 *  are no globes here, my friend.  This has nothing to do with earth or its
 *  nations.  In fact, at this point I'm not even sure I'm using the right term
 *  anymore.  It sounds kind of weird in my head now.
 *
*******************************************************************************/
#ifndef PROTOTYPES_H
#define PROTOTYPES_H

/*
--------------------------------------------------------------------------------
                              FUNCTION PROTOTYPES
--------------------------------------------------------------------------------
*/

/*  Check args - defined in args.cpp */
int check_args( int argc, char *argv[] );

/*  Init all SDL stuff - defined in init.cpp */
extern bool init( void );

/*  Handle all events - defined in events.cpp */
extern void handle_events( SDL_Event &e );

/*  Handles all of the rendering - defined in render.cpp */
extern void render( void );

/*  Render the menu screen - defined in render.cpp */
extern void render_menu( void );

/*  Handles main screen rendering - defined in render.cpp */
extern void render_main( void );

/*  Render the game over screen - defined in render.cpp */
extern void render_game_over( void );

/*  Render the high score screen - defined in render.cpp */
extern void render_high_scores( void );

/*  Render the 'enter high score' screen - defined in render.cpp */
extern void render_enter_high_score( void );

/*  Render the transition screen(s) - defined in transition.cpp */
extern void render_transition( void );

/*
 *  Render two textures with a fade that alternates in direction between them,
 *  creating a 'pulse' effect.  Helps if they're the same texture, only
 *  different colors
 *
 *  Defined in render.cpp
 */
extern void render_pulse( Texture *tex1, Texture *tex2, int speed );

/*  Adjust border alpha - defined in render.cpp */
extern void adjust_border( void );

/*  Render border using texture dimensions - defined in render.cpp */
extern void render_texture_border( Texture *texture );

/*
 *  Render border using given points - defined in render.cpp
 *
 *  Points:
 *      tl  Top left
 *      tr  Top right
 *      br  Bottom right
 *      bl  Bottom left
 */
extern void render_border( SDL_Point tl, SDL_Point tr, SDL_Point br,
        SDL_Point bl );

/*  Render the help screen - defined in render.cpp */
extern void render_help( void );

/*  Render the credits screen - defined in render.cpp */
extern void render_credits( void );

/*  Draw a border around the player's boundary - defined in border.cpp */
extern void draw_border( void );

/*  Closes out SDL and gets rid of objects - defined in close.cpp */
extern void close( void );

/*  Loads all media for the game - defined in load.cpp */
extern bool load_media( void );

/*  Load panel object - defined in load.cpp */
extern void load_panel( void );

/*  Loads player object - defined in load.cpp */
extern void load_player( void );

/*  Loads enemy objects  - defined in load.cpp */
extern void load_enemy( void );

/*  Load fonts - defined in load.cpp */
extern bool load_fonts( void );

/*  Loads the star field -- defined in load.cpp */
extern void load_starfield( void );

/*  Create the scores object - defined in load.cpp */
extern bool load_scores( void );

/*  Create the initials objects - defined in load.cpp */
extern bool load_initials( void );

/*  Load help screen - defined in load.cpp */
extern bool load_help( void );

/*  Load credits screen */
extern bool load_credits( void );

/*  Load the menu screen */
extern bool load_menu( void );

/*  Updates the player and enemies - defined in update.cpp */
extern void update( void );

/*  Check for rectangular collisions - defined in collision.cpp */
extern bool check_collision_box( SDL_Rect &rectA, SDL_Rect &rectB );

/*  Check for per-pixel collisions - defined in collision.cpp */
extern bool check_collision_colliders( std::vector<Collider> &collidersA,
        std::vector<Collider> &collidersB );

/*  Checks for collision between a rectangle and a circle - collision.cpp */
extern bool check_collision_rect_circ( SDL_Rect &rect, Circle &circ );

/*  Check for collision between a circle and a circle - collision.cpp */
extern bool check_collision_circ( Circle &a, Circle &b );

/*  Increase or decrase the warp speed - defined int warp.cpp */
extern void warp_up( void );
extern void warp_down( void );
extern void warp_update( void );

/*  Initialize the transition integers - defined in transition.cpp */
extern void init_transition( void );

/*  Handle vertical screen transitions - defined in transition.cpp */
extern void transition_vertical( int direction );

/*  Handle horizontal screen transitions - defined in transition.cpp */
extern void transition_horizontal( int direction );

/*  Begin the transition - defined in transition.cpp */
extern void start_transition( int toScreen, int directionKey );

/*  Resets all the important game stuff - defined in reset.cpp */
extern void reset( void );

/*  Game over initialization - defined in gameover.cpp */
extern void game_over( void );

/*  Enter high score initialization - defined in enterhighscore.cpp */
extern void enter_high_score( void );

/*  Toggle all sounds on / off - defined in sounds.cpp */
extern void toggle_sounds( void );

/*  Toggle all music on / off - defined in sounds.cpp */
extern void toggle_music( void );

/*  Mute or unmute everything - defined in sounds.cpp */
extern void mute( bool muting );

/*  Create an OSD to display - defined in osd.cpp */
extern void osd( const char *string );

/*  Update the OSD if it exists - defined in osd.cpp */
extern void update_osd( void );

/*  Render the OSD if it exists - defined in osd.cpp */
extern void render_osd( void );

#endif
