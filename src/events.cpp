/*******************************************************************************
 *  events.cpp
 *
 *  This file controls all input received from the player, routing events to
 *  their correct places or otherwise taking appropriate action.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                   SET LETTER
--------------------------------------------------------------------------------
 *  Used on the 'enter high score' screen, when the player just starts typing
 *  on the keyboard.  Sets the currently highlighted initial to the letter
 *  pressed and then switches focus to the next letter.
*/
void set_letter( char key )
{
    /*  Init focus variable to zero -- it will be reset later */
    int focus = 0;

    /*
     *  Go through the initials, checking for focus, and sending the given key
     *  value to whichever initial has the focus
     */
    for( int i = 0; i < 3; ++i )
    {
        if( initials[ i ]->has_focus() )
        {
            initials[ i ]->set_letter( key );
            initials[ i ]->update_letter_texture();
            initials[ i ]->set_focus( false );

            /*  Switch focus to the next initial */
            focus = i + 1;
        }
    }

    /*  Correct focus if it went too high / low */
    if( focus < 0 )
        focus = 2;
    else if( focus > 2 )
        focus = 0;

    /*  Move on */
    initials[ focus ]->set_focus( true );
}



/*
--------------------------------------------------------------------------------
                                  SWITCH FOCUS
--------------------------------------------------------------------------------
 *  Used on the 'enter high score' screen, when the user presses the left or
 *  right arrow key.
*/
void switch_focus( int direction )
{
    /*  Init current focus to zero */
    int currentFocus = 0;

    /*  Find the initial that has focus with a for loop */
    for( int i = 0; i < 3; ++i )
    {
        if( initials[ i ]->has_focus() )
        {
            /*  Set focus integer to match the initial with focus */
            currentFocus = i;
            break;
        }
    }

    /*  Adjust the focus in whichever direction the user indicated */
    currentFocus += direction;

    /*
     *  Here we correct the focus:  Too far left and we wrap around to the max
     *  value (2), putting the focus on the right-most initial.  Too far right
     *  and we wrap around to 0, the left-most initial.
     */
    if( currentFocus < 0 )
        currentFocus = 2;
    else if( currentFocus > 2 )
        currentFocus = 0;

    /*
     *  Go through the initials and correct their 'focus' value to true if their
     *  position in the initials array corresponds with the current focus
     *  variable or false if it doesn't.
     */
    for( int i = 0; i < 3; ++i )
    {
        if( i == currentFocus )
            initials[ i ]->set_focus( true );
        else
            initials[ i ]->set_focus( false );
    }
}



/*
--------------------------------------------------------------------------------
                                 SWITCH LETTER
--------------------------------------------------------------------------------
 *  Used by the 'enter high score' screen, this function adjusts the selected
 *  initial's letter 'up' or 'down' according to which direction was indicated
 *  by the user; -1 for up, 1 for down.  -1 is given when the user presses up
 *  on the keyboard or scrolls the mouse wheel up.  +1 is given when the user
 *  presses down on the keyboard or scrolls the mouse wheel down.
*/
void switch_letter( int direction )
{
    /*
     *  Go through the initials array and switch the letter for whichever
     *  initial has focus according to the direction given.
     */
    for( int i = 0; i < 3; ++i )
    {
        if( initials[ i ]->has_focus() )
        {
            if( direction < 0 )
                initials[ i ]->letter_up();
            else if( direction > 0 )
                initials[ i ]->letter_down();
        }
    }
}



/*
--------------------------------------------------------------------------------
                                  MAIN EVENTS
--------------------------------------------------------------------------------
 *  This function handles all events on the main screen - that is, the screen
 *  where the player is actually playing the game rather than a menu or some
 *  information screen.
*/
void events_main( SDL_Event &e )
{
    /*  Send all mouse motion events straight to the player class */
    if( e.type == SDL_MOUSEMOTION )
        player.move_mouse();

    /*  Mouse button events are less complex and can be handled here */
    if( e.type == SDL_MOUSEBUTTONUP )
    {
        /*  Left click:  Honk horn */
        if( e.button.button == SDL_BUTTON_LEFT )
            player.honk();

        /*  Right-click:  Activate power (or make an 'engine stall' sound) */
        if( e.button.button == SDL_BUTTON_RIGHT )
            player.init_power();

        /*  Middle click:  Pause the game */
        if( e.button.button == SDL_BUTTON_MIDDLE )
        {
            /*  Pause the game and transition to the menu screen */
            gamePaused = true;
            start_transition( SCREEN_MENU, DIRECTION_DOWN );

            /*  If the music is playing, pause it */
            if( Mix_PlayingMusic() == 1 )
                Mix_PauseMusic();
        }
    }


    /*  If the player has pressed (and released) a key */
    if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            /*
             *  If the player pressed ESCAPE, pause the game, transition to the
             *  menu screen and pause the music.
             */
            case SDLK_ESCAPE:
                gamePaused = true;
                start_transition( SCREEN_MENU, DIRECTION_DOWN );

                if( Mix_PlayingMusic() == 1 )
                    Mix_PauseMusic();

                break;

            /*  If the player pressed Q, quit the game */
            case SDLK_q:
                quit = true;
                break;

            /*  If the player pressed S, toggle sound effects on/off */
            case SDLK_s:
                toggle_sounds();
                break;

            /*  If the player pressed M, toggle the music on/off */
            case SDLK_m:
                toggle_music();
                break;

            /*  SPACE honks the horn */
            case SDLK_SPACE:
                player.honk();
                break;

            /*  SHIFT activates (or attempt to activate) the power */
            case SDLK_LSHIFT:
                player.init_power();
                break;
        }
    }
}


/*
--------------------------------------------------------------------------------
                                  MENU EVENTS
--------------------------------------------------------------------------------
 *  This function handles events received from the player on the menu screen.
*/
void events_menu( SDL_Event &e )
{
    /*  Just send these to the menuScreen object */
    menuScreen->handle_events( e );
}



/*
--------------------------------------------------------------------------------
                                GAME OVER EVENTS
--------------------------------------------------------------------------------
 *  This function handles events received from the player on the game over
 *  screen.
*/
void events_game_over( SDL_Event &e )
{
    /*  If the player clicked the mouse */
    if( e.type == SDL_MOUSEBUTTONUP )
    {
        /*
         *  We check to see that a slight delay has passed before processing
         *  events; that way, a player can't accidentally click himself off of
         *  this screen to parts unknown before he's even realized that his
         *  space car was destroyed.
         */
        if( ( SDL_GetTicks() - miscTicks ) > (10 * FPS) )
        {
            /*  Left mouse button */
            if( e.button.button == SDL_BUTTON_LEFT )
            {
                /*  If their score is good enough, they can register it */
                if( gScores->score_qualifies( currentScore ) )
                    enter_high_score();     //  Send to 'enter high scores' scrn

                /*
                 *  Otherwise, they are instead given the opportunity to gawk at
                 *  the prowess of superior space car pilots by sending them
                 *  directly to the high scores screen.
                 */
                else
                {
                    /*  Update all the scores */
                    gScores->update();

                    /*  Transition to high scores screen */
                    start_transition( SCREEN_HIGH_SCORES, DIRECTION_LEFT );
                }
            }

            /*
             *  The right mouse button always means "I just want to get back to
             *  playing, and I don't give a shit about seeing or entering any
             *  scores".
             */
            else if( e.button.button == SDL_BUTTON_RIGHT )
            {
                /*  Reset everything */
                reset();

                /*  Transition back to the main screen */
                start_transition( SCREEN_MAIN, DIRECTION_DOWN );
            }
        }
    }


    /*  If the player has pressed a key */
    if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            /*  Escape is the same as RMB above; return to play immediately */
            case SDLK_ESCAPE:
                reset();
                start_transition( SCREEN_MAIN, DIRECTION_DOWN );
                break;

            /*  Q, as always, quits the game */
            case SDLK_q:
                quit = true;
                break;

            /*  Any other key will act as LMB above */
            default:
                if( gScores->score_qualifies( currentScore ) )
                    enter_high_score();
                else
                {
                    gScores->update();
                    start_transition( SCREEN_HIGH_SCORES, DIRECTION_LEFT );
                }
                break;
        }
    }
}



/*
--------------------------------------------------------------------------------
                           HIGH SCORES SCREEN EVENTS
--------------------------------------------------------------------------------
 *  This function defines the behavior of the high scores screen according to
 *  input received from the player.
*/
void events_high_scores( SDL_Event &e )
{
    /*  If the player clicked the mouse */
    if( e.type == SDL_MOUSEBUTTONUP )
    {
        /*
         *  LMB either returns to the menu or returns to play, depending on if
         *  the player has paused/just started the game, or has died and is just
         *  waiting to get back to play.
         */
        if( e.button.button == SDL_BUTTON_LEFT )
        {
            /*  If paused / just started, return to menu */
            if( gamePaused || currentScore == 0 )
                start_transition( SCREEN_MENU, DIRECTION_RIGHT );

            /*  If previously killed, reset everything and return to play */
            else
            {
                reset();
                start_transition( SCREEN_MAIN, DIRECTION_DOWN );
            }
        }

        /*  If the player clicked the right mouse button */
        else if( e.button.button == SDL_BUTTON_RIGHT )
        {
            /*  If the player has paused or just started, return to menu */
            if( gamePaused || currentScore == 0 )
                start_transition( SCREEN_MENU, DIRECTION_RIGHT );

            /*
             *  If the player was killed and their score qualified, return to
             *  play; this is here to prevent people from entering their score
             *  multiple times.  I'm too lazy to fix it the proper way, at least
             *  for now.
             */
            else if( gScores->score_qualifies( currentScore ) )
            {
                reset();
                start_transition( SCREEN_MAIN, DIRECTION_DOWN );
            }

            /*
             *  If their score didn't qualify, they can return to the game over
             *  screen to be reminded of how big a loser they are
             */
            else
                start_transition( SCREEN_GAME_OVER, DIRECTION_RIGHT );
        }
    }


    /*  If the player pressed and then released a key */
    if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            /*  Q quits */
            case SDLK_q:
                quit = true;
                break;

            /*  Anything else returns to play or returns to menu */
            default:
                if( gamePaused || currentScore == 0 )
                    start_transition( SCREEN_MENU, DIRECTION_RIGHT );
                else
                {
                    reset();
                    start_transition( SCREEN_MAIN, DIRECTION_DOWN );
                }
                break;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                   HIGH SCORE
--------------------------------------------------------------------------------
 *  This function does the actual entering of the score according to both the
 *  current score and the selected initials
*/
void enter_score( void )
{
    /*  A short string to hold the character (initials) data in */
    char jHancock[ 3 ];

    /*  Grab the initials, put them into the string */
    for( int i = 0; i < 3; ++i )
    {
        jHancock[ i ] = initials[ i ]->get_letter();
    }

    /*  Update the scores with the current score and the initials */
    gScores->add_score( currentScore, jHancock );
    gScores->update();

    /*  Go back to the high scores screen */
    start_transition( SCREEN_HIGH_SCORES, DIRECTION_LEFT );
}



/*
--------------------------------------------------------------------------------
                            ENTER HIGH SCORE EVENTS
--------------------------------------------------------------------------------
 *  Event handling for the 'enter high score' screen
*/
void events_enter_high_score( SDL_Event &e )
{

    /*  If the player clicked the mouse */
    if( e.type == SDL_MOUSEBUTTONUP )
    {
        /*  Right mouse button -- move backward through the initials */
        if( e.button.button == SDL_BUTTON_RIGHT )
        {
            /*  If they haven't clicked anything yet, go back to game over */
            if( initialsClicked == 0 )
                start_transition( SCREEN_GAME_OVER, DIRECTION_DOWN );

            /*  Otherwise, switch the focus backward */
            else
            {
                switch_focus( -1 );
                --initialsClicked;      //  Decrement initials clicked
            }
        }

        /*  Left mouse button -- progress forward through initials */
        else if( e.button.button == SDL_BUTTON_LEFT )
        {
            /*
             *  If they've already selected two initials previously, this final
             *  selected initial will enter the score
             */
            if( initialsClicked == 2 )
                enter_score();

            /*  Otherwise, move the focus forward through the initials array */
            else
            {
                switch_focus( 1 );
                ++initialsClicked;      //  Increment initials clicked
            }
        }
    }


    /*  Mouse wheel cycles through letters */
    if( e.type == SDL_MOUSEWHEEL )
    {
        /*  Move 'up' or 'down' through the alphabet with the mouse wheel */
        if( e.wheel.y < 0 )
            switch_letter( 1 );
        else if( e.wheel.y > 0 )
            switch_letter( -1 );
    }


    /*  Keyboard does various things.  Just look. */
    if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            /*  Escape returns to the game over screen */
            case SDLK_ESCAPE:
                start_transition( SCREEN_GAME_OVER, DIRECTION_DOWN );
                break;

            /*  Left arrow key moves backward through initials */
            case SDLK_LEFT:
                switch_focus( -1 );
                break;

            /*  Right arrow key move forward through initials */
            case SDLK_RIGHT:
                switch_focus( 1 );
                break;

            /*  Up arrow key moves 'upward' through the alphabet */
            case SDLK_UP:
                switch_letter( -1 );
                break;

            /*  Down arrow key moves 'downward' through the alphabet */
            case SDLK_DOWN:
                switch_letter( 1 );
                break;

            /*  Return key confirms the initials selection */
            case SDLK_RETURN:
                enter_score();
                break;

            /*
             *  By default, any other key (specifically, any other ASCII
             *  character between the lowercase 'a' and lowercase 'z') is chosen
             *  as the letter for the selected inital.  Focus switches forward
             *  after every keypress.
             */
            default:
                if( e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z )
                    set_letter( e.key.keysym.sym );
                break;
        }
    }
}



/*
--------------------------------------------------------------------------------
                          HELP / CREDITS SCREEN EVENTS
--------------------------------------------------------------------------------
 *  This function handles events on the help screen and the credits screen; they
 *  both behave in exactly the same way, except for the direction of the
 *  transition
*/
void events_help_credits( SDL_Event &e )
{
    //  Set the direction of the transition according to which screen we're on
    int direction;
    if( currentScreen == SCREEN_HELP )
        direction = DIRECTION_UP;
    else if( currentScreen == SCREEN_CREDITS )
        direction = DIRECTION_LEFT;

    /*  If the player clicked the mouse, just return to the menu */
    if( e.type == SDL_MOUSEBUTTONUP )
        start_transition( SCREEN_MENU, direction );

    /*  If the player pressed a button */
    if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            /*  If the button was 'Q', quit the game */
            case SDLK_q:
                quit = true;
                break;

            /*  Otherwise, return to the menu */
            default:
                start_transition( SCREEN_MENU, direction );
                break;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                 HANDLE EVENTS
--------------------------------------------------------------------------------
 *  Master event handler function; this routes events to their appropriate
 *  places according to the current screen.
*/
void handle_events( SDL_Event &e )
{
    /*  Poll events here for a couple of special cases */
    while( SDL_PollEvent( &e ) != 0 )
    {
        /*  If the user clicks the X button, quit the game */
        if( e.type == SDL_QUIT )
            quit = true;

        if( e.type == SDL_KEYUP )
        {

            /*  If the player hit the 'G' button, toggle mouse grabbing */
            if( e.key.keysym.sym == SDLK_g )
            {
                if( SDL_GetRelativeMouseMode() == SDL_TRUE )
                    SDL_SetRelativeMouseMode( SDL_FALSE );
                else
                    SDL_SetRelativeMouseMode( SDL_TRUE );
            }
        }


        /*  Route events to their proper functions */
        if( currentScreen == SCREEN_MAIN )
            events_main( e );
        else if( currentScreen == SCREEN_MENU )
            events_menu( e );
        else if( currentScreen == SCREEN_GAME_OVER )
            events_game_over( e );
        else if( currentScreen == SCREEN_ENTER_HIGH_SCORE )
            events_enter_high_score( e );
        else if( currentScreen == SCREEN_HIGH_SCORES )
            events_high_scores( e );
        else if( currentScreen == SCREEN_HELP || currentScreen ==SCREEN_CREDITS)
            events_help_credits( e );
    }

    /*  This is outside the poll event loop to prevent keyboard delays */
    player.move_keyboard();

}
