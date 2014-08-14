/*******************************************************************************
 *  args.cpp
 *
 *  This file defines how the arguments are parsed by the program.  Only a few
 *  are checked for; anything else triggers a warning but the program continues
 *  to execute as normal.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                   PRINT HELP
--------------------------------------------------------------------------------
 *  Prints help text.
*/
void print_help( void )
{
    printf("Usage:  belted [OPTION]\n\n");
    printf("Belted is a simplistic arcade-style game in which you dodge\n");
    printf("asteroids, as well as honk at them if the mood strikes you.\n");
    printf("If you're close enough, you'll earn extra points by doing so.\n\n");

    printf("While the game can be played with a keyboard, it was designed\n");
    printf("with using the mouse in mind.\n\n");

    printf("To see more info on the controls, use the --controls command.\n\n");

    printf("Options:\n\n");
    printf("  -h or --help:\t\tPrint this help text\n");
    printf("  -v or --version:\tPrint version and author info\n");
    printf("  -c or --controls:\tPrint a comprehensive list of controls\n");
    printf("  -s or --scores:\tPrint the hall of fame to your terminal\n");
    printf("  -l or --limit-fps:\tLimit FPS to 60, disable vsync\n");
    printf("  -m or --mute:\t\tStart with music and sound muted\n");
    printf("  -S or --story:\tPrint the backstory to your terminal\n");
}


/*
--------------------------------------------------------------------------------
                                 PRINT VERSION
--------------------------------------------------------------------------------
 *  Prints version and author info.
*/
void print_version( void )
{
    printf("Belted version %s\n", VERSION.c_str() );
    printf("James Hendrie <hendrie.james@gmail.com>\n");
    printf("http://www.someplacedumb.net/games\n");
}


/*
--------------------------------------------------------------------------------
                                 PRINT CONTROLS
--------------------------------------------------------------------------------
 *  Prints a more comprehensive list of controls for the user.
*/
void print_controls( void )
{
    printf("CONTROLS:\n\n");
    printf("Mouse controls\n");
    printf("  Move the mouse to move your ship\n");
    printf("  Left click to honk or progress through screens\n");
    printf("  Right click to activate power or go back through screens\n");
    printf("  Scroll the mouse wheel to select menu entries\n");
    printf("  Click the mouse wheel to bring the menu up or down\n\n");

    printf("Keyboard controls\n");
    printf("  Use the ARROW KEYS to move the ship or navigate the menu\n");
    printf("  Press SPACE to honk at asteroids or progress through screens\n");
    printf("  Press SHIFT to activate your special charge power\n");
    printf("  Press ESCAPE to go back through screens\n");
    printf("  Press 'S' to toggle sounds\n");
    printf("  Press 'M' to toggle music\n");
    printf("  Press 'Q' to quit\n\n");

    printf("Also, pressing 'G' during play or in the main menu will toggle\n");
    printf("mouse grabbing.\n\n");

    printf("Seriously, though.  For real.  Use the mouse.  Trust me.\n");
}


/*
--------------------------------------------------------------------------------
                                  PRINT SCORES
--------------------------------------------------------------------------------
 *  Prints the scores to the terminal.
*/
bool print_scores( void )
{
    /*  Create an instance of the ScoreRecord struct to hold data */
    struct ScoreRecord record;

    /*  Open the game's data file */
    FILE *fp = fopen( DAT_FILE_PATH.c_str(), "rb" );
    if( fp == NULL )
    {
        printf("ERROR:  Could not open scores file\n");
        return( false );
    }

    /*
     *  Print the header and then read each record from the file one by one,
     *  printing it to the terminal.
     */
    printf("================\n");
    printf("  HALL OF FAME  \n");
    printf("================\n\n");
    for( int i = 0; i < 10; ++i )
    {
        if( fread( &record, sizeof( struct ScoreRecord ), 1, fp ) == 0 )
            printf("WARNING:  Zero bytes read from file\n");

        printf("%02d.  %s  %06u\n", i + 1, record.initials, record.score );
    }

    /*  Close the file */
    fclose( fp );

    return( true );
}



/*
--------------------------------------------------------------------------------
                                  PRINT STORY
--------------------------------------------------------------------------------
 *  Prints a little bit of story text.
*/
bool print_story( void )
{
    /*  Open the story file for reading */
    FILE *fp = fopen( STORY_FILE_PATH.c_str(), "r" );
    if( fp == NULL )
    {
        printf("ERROR:  Cannot open story file\n");
        return( false );
    }

    /*  Write it all to stdout */
    int ch = '\0';
    while( ( ch = fgetc( fp ) ) != EOF )
    {
        putchar( ch );
    }

    /*  Close the file */
    fclose( fp );

    return( true );
}


/*
--------------------------------------------------------------------------------
                                   CHECK ARGS
--------------------------------------------------------------------------------
 *  The 'master' function for this file; decides how to handle each of the valid
 *  arguments and calls the appropriate function if necessary.  Invalid
 *  arguments generate a warning but are otherwise ignored.
*/
int check_args( int argc, char *argv[] )
{
    /*  String to hold the arg in for easy string comparison */
    std::string arg;

    /*  While (/if) there's at least one argument (not incl. the program) */
    while( argc > 1 )
    {
        /*  Copy the arg string constant to the std::string object */
        arg.assign( argv[1] );

        /*  If they want help */
        if( arg == "-h" || arg == "--help" )
        {
            print_help();
            return( -1 );
        }

        /*  If they want version and author info */
        else if( arg == "-v" || arg == "--version" )
        {
            print_version();
            return( -1 );
        }

        /*  If they want a full list of controls */
        else if( arg == "-c" || arg == "--controls" )
        {
            print_controls();
            return( -1 );
        }

        /*  If they want to see the current scores */
        else if( arg == "-s" || arg == "--scores" )
        {
            if( ! print_scores() )
                return( 1 );
            else
                return( -1 );
        }

        /*  If they want the story */
        else if( arg == "-S" || arg == "--story" )
        {
            if( ! print_story() )
                return( 1 );
            else
                return( -1 );
        }

        /*  If they want to mute the sound effects and music */
        else if( arg == "-m" || arg == "--mute" )
        {
            /*  Set music and sound to false */
            playSound = false;
            playMusic = false;
        }

        /*  If they want to limit FPS */
        else if( arg == "-l" || arg == "--limit-fps" )
            limitFPS = true;

        /*  Any other argument generates a warning */
        else
            printf("WARNING:  Unknown option:  '%s'\n", argv[1] );

        /*
         *  By decrementing the arg count we let the program know when it needs
         *  to quit checking for args.  By increasing the arg pointer, we make
         *  sure we're pointing at a new arg every loop.
         */
        --argc;
        ++argv;
    }

    /*  Return success by default */
    return( 0 );
}
