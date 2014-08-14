/*******************************************************************************
 *  scores.cpp
 *
 *  This file defines the functions of the scores class, which tracks the top
 *  ten scores, reads from / writes to the scores file, and handles the display
 *  of the score screen.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                 COMPARE SCORES
--------------------------------------------------------------------------------
 *  This is a comparison test written to be used by the scores list's sort
 *  method.
*/
bool compare_scores( struct ScoreRecord r1, struct ScoreRecord r2 )
{
    return( r2.score > r1.score );
}



/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
*/
Scores::Scores( void )
{
    /*  Set our values to nothing... NOTHING!!!!!!!!!!!! */
    mHighScore = 0;

    /*  Set the number of high scores to track */
    mScoresToKeep = 10;

    /*  File stuff */
    mFilePath = DAT_FILE_PATH;
    mFileTextPath = TXT_FILE_PATH;
    mScoreFile = NULL;

    /*  Clear the score textures just for fun */
    mScoreTextures.clear();

    /*  Init the other misc textures */
    mNewText = NULL;
    mHallOfFameText = NULL;
    mHallOfFameTextWhite = NULL;
    mHallOfFameInfo1 = NULL;
    mHallOfFameInfo2 = NULL;

    /*  The 'new' text is not displayed by default */
    mNew = false;
}



/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Scores::~Scores( void )
{
    /*  Free the textures */
    free_textures();

    /*  Set all the things to zero */
    mHighScore = 0;
}




/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
 *  Free all of the text textures
*/
void Scores::free_textures( void )
{
    /*  Free any score textures that exist and null the pointers */
    mScoreTextures.clear();


    /*  Blinking 'new score' indicator */
    if( mNewText != NULL )
    {
        delete mNewText;
        mNewText = NULL;
    }


    /*  Header (cyan) */
    if( mHallOfFameText != NULL )
    {
        delete mHallOfFameText;
        mHallOfFameText = NULL;
    }

    /*  Header (white) */
    if( mHallOfFameTextWhite != NULL )
    {
        delete mHallOfFameTextWhite;
        mHallOfFameTextWhite = NULL;
    }

    /*  "Press any key to return to menu" */
    if( mHallOfFameInfo1 != NULL )
    {
        delete mHallOfFameInfo1;
        mHallOfFameInfo1 = NULL;
    }

    /*  "Or press 'q' to quit" */
    if( mHallOfFameInfo2 != NULL )
    {
        delete mHallOfFameInfo2;
        mHallOfFameInfo2 = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Initialize the scores instance by calling functions to read the scores from
 *  the scores file and creating all of the score text textures.
*/
bool Scores::init( void )
{
    /*  Read (or generate) the current high scores */
    read_scores( mFilePath.c_str() );

    /*  Create text textures for all of the high scores */
    if( ! create_score_textures() )
    {
        printf("ERROR:  Could not create score textures!\n");
        return( false );
    }

    return( true );
}




/*
--------------------------------------------------------------------------------
                             CREATE SCORE TEXTURES
--------------------------------------------------------------------------------
 *  Create the score textures and load text into them.
*/
bool Scores::create_score_textures( void )
{
    /*  Free the textures if they exist */
    free_textures();

    /*  Sort the scores so that they're in order */
    mScores.sort( compare_scores );

    /*  Reverse order so that the highest number is on top */
    mScores.reverse();

    /*  Create the texture pointers and put them in the array */
    for( unsigned int i = 0; i < mScores.size(); ++i )
    {
        Texture *tex = new Texture();
        mScoreTextures.push_back( tex );
    }

    /*  We'll need these for the following loop */
    std::list<ScoreRecord>::iterator s;
    int textureCount = 0;

    /*  Create some score textures baby */
    for( s = mScores.begin(); s != mScores.end(); ++s )
    {
        char scoreString[ 16 ];
        snprintf( scoreString, 16, "%06u  %s", s->score, s->initials );
        if( ! mScoreTextures[ textureCount ]->create_texture_from_string(
                    gFontSmall, scoreString, colors[ COLOR_WHITE ] ) )
        {
            printf("Failed to create score texture\n");
            return( false );
        }

        ++textureCount;
    }


    /*  Create the 'new' text texture */
    mNewText = new Texture();
    if( ! mNewText->create_texture_from_string( gFontTiny, "NEW!",
                colors[ COLOR_WHITE ] ) )
    {
        printf("Could not create 'new' text texture\n");
        return( false );
    }

    /*  Set 'new' text to flashing */
    mNewText->set_flashing( true );

    /*  Create the 'hall of fame' text texture */
    mHallOfFameText = new Texture();
    if( ! mHallOfFameText->create_texture_from_string( gFont, "HALL OF FAME",
                colors[ COLOR_CYAN ] ) )
    {
        printf("Could not create 'hall of fame' text texture\n");
        return( false );
    }

    /*  Create the 'hall of fame' text texture (white version) */
    mHallOfFameTextWhite = new Texture();
    if( ! mHallOfFameTextWhite->create_texture_from_string( gFont,
                "HALL OF FAME", colors[ COLOR_WHITE ] ) )
    {
        printf("Could not create 'hall of fame' text texture (white)\n");
        return( false );
    }

    /*  Set the texture to transparent */
    mHallOfFameTextWhite->set_alpha( 0 );


    /*  Create the Hall of Fame info string */
    std::string hofStr;
    if( gamePaused || currentScore == 0 )
        hofStr = "Press any key to return to menu";
    else
        hofStr = "Press any key to return to play";

    mHallOfFameInfo1 = new Texture();
    if( ! mHallOfFameInfo1->create_texture_from_string( gFontTiny,
                hofStr.c_str(), colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create hall of fame info text texture 1\n");
        return( false );
    }

    mHallOfFameInfo2 = new Texture();
    if( ! mHallOfFameInfo2->create_texture_from_string( gFontTiny,
                "Or press 'Q' to quit", colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create hall of fame info text texture 2\n");
        return( false );
    }


    return( true );
}



/*
--------------------------------------------------------------------------------
                                   OPEN FILE
--------------------------------------------------------------------------------
 *  Assign the score file FILE pointer to the given path, and open it with the
 *  given mode.  If that failed, report as much.
*/
bool Scores::open_file( const char *path, const char *mode )
{
    /*  Open the score file for reading */
    mScoreFile = fopen( path, mode );

    /*  Return success */
    return( mScoreFile != NULL );
}




/*
--------------------------------------------------------------------------------
                                  READ SCORES
--------------------------------------------------------------------------------
 *  Read scores records from the scores file, storing them into the score
 *  records list.
*/
void Scores::read_scores( const char *path )
{
    /*  Clear the scores list */
    mScores.clear();

    /*  If we can open the file, read from it */
    if( open_file( path, "rb" ) )
    {
        for( int r = 0; r < mScoresToKeep; ++r )
        {
            /*  Create a new record to store information in */
            struct ScoreRecord record;

            /*  Read data from disk into that record */
            if( fread( &record, sizeof( struct ScoreRecord ), 1, mScoreFile )
                    == 0)
            {
                printf("WARNING:  Zero bytes read from file\n");
            }

            /*  Save the information into the scores list */
            mScores.push_back( record );
        }

        /*  Close the file */
        fclose( mScoreFile );
    }

    /*  If we were unable to open the file */
    else
    {
        /*  Let the user know they suck */
        printf("WARNING:  Could not open score file '%s' for reading.\n",
                mFilePath.c_str() );

        /*  Create a bunch of fake scores */
        for( int s = 0; s < mScoresToKeep; ++s )
        {
            struct ScoreRecord record;
            record.score = 0;
            record.initials[ 0 ] = 'A';
            record.initials[ 1 ] = 'A';
            record.initials[ 2 ] = 'A';
            record.initials[ 3 ] = '\0';
            mScores.push_back( record );
        }
    }

}



/*
--------------------------------------------------------------------------------
                               WRITE SCORES (DAT)
--------------------------------------------------------------------------------
 *  This writes the score records to the scores.dat file, which is the binary
 *  file where the scores are kept for use by the program itself.
*/
void Scores::write_scores_dat( const char *path )
{
    /*  If the file can be opened in binary write mode */
    if( open_file( path, "wb" ) )
    {
        /*  Sort scores and reverse so highest is at the top */
        mScores.sort( compare_scores );
        mScores.reverse();

        /*  If the scores list is too big, resize it */
        if( mScores.size() > (unsigned int)mScoresToKeep )
            mScores.resize( mScoresToKeep );

        /*  Write all of the files to disk */
        std::list<ScoreRecord>::iterator s;
        for( s = mScores.begin(); s != mScores.end(); ++s )
        {
            /*  Create a blank record */
            struct ScoreRecord record;

            /*  Copy all the stuff from the iterator to the new record */
            record.score = s->score;
            record.initials[ 0 ] = s->initials[ 0 ];
            record.initials[ 1 ] = s->initials[ 1 ];
            record.initials[ 2 ] = s->initials[ 2 ];
            record.initials[ 3 ] = s->initials[ 3 ];

            /*  Write the new record to disk */
            fwrite( &record, sizeof( struct ScoreRecord ), 1, mScoreFile );
        }

        /*  Close the file */
        fclose( mScoreFile );
    }

    /*  If the file could not be opened for writing */
    else
    {
        printf("ERROR:  Could not open score file '%s' for writing.\n",
                mFilePath.c_str() );
    }
}



/*
--------------------------------------------------------------------------------
                               WRITE SCORES (TXT)
--------------------------------------------------------------------------------
 *  This function writes out a text file with all of the scores in it for the
 *  user's convenience.
*/
void Scores::write_scores_txt( const char *path )
{
    /*  If the file can be opened in write mode (non-binary) */
    if( open_file( path, "w" ) )
    {
        /*  Sort scores and reverse so highest is at the top */
        mScores.sort( compare_scores );
        mScores.reverse();

        /*  If the scores list is too big, resize it */
        if( mScores.size() > (unsigned int)mScoresToKeep )
            mScores.resize( mScoresToKeep );

        /*  Write all of the files to disk */
        std::list<ScoreRecord>::iterator s;
        int place = 0;
        for( s = mScores.begin(); s != mScores.end(); ++s )
        {
            /*
             *  Increment this as we go along so we can separate the men from
             *  the boys.
             */
            ++place;

            /*  Create a string to hold our text */
            char scoreStr[ 32 ];
            snprintf( scoreStr, 32, "%02d\t%s\t%06u\n", place, s->initials,
                    s->score );

            /*  Write the string to disk */
            fputs( scoreStr, mScoreFile );
        }

        /*  Close the file */
        fclose( mScoreFile );
    }

    /*  If the file could not be opened in write mode */
    else
    {
        printf("ERROR:  Could not open score file '%s' for writing.\n",
                mFilePath.c_str() );
    }
}



/*
--------------------------------------------------------------------------------
                                  WRITE SCORES
--------------------------------------------------------------------------------
 *  This function calls both the write_scores_dat() function and the
 *  write_scores_txt() function.  I just like to keep them separate is all.
*/
void Scores::write_scores( void )
{
    write_scores_dat( mFilePath.c_str() );
    write_scores_txt( mFileTextPath.c_str() );
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Scores::update( void )
{
    /*  SORT THE LIST AND RESIZE IT TO CULL THE WEAK */
    mScores.sort( compare_scores );
    mScores.reverse();

    /*  Resize the scores if necessary */
    if( mScores.size() > (unsigned int)mScoresToKeep )
        mScores.resize( mScoresToKeep );

    /*  Write the scores to disk */
    write_scores();
    write_scores_dat( mFilePath.c_str() );
    write_scores_txt( mFileTextPath.c_str() );

    /*  Re-create the score textures */
    create_score_textures();

    /*  Grab the highest score */
    mHighScore = mScores.begin()->score;

    /*  Create the new high score text */
    char newHighScore[ 16 ];
    snprintf( newHighScore, 16, "%06u", mHighScore );
    highScoreText->create_texture_from_string( gFontTiny, newHighScore,
            colors[ COLOR_WHITE ] );
}


/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Scores::render( void )
{
    /*  Render the header */
    render_header();

    /*  A rect to store position / dimension info in */
    SDL_Rect r;

    int texCount = 0;
    std::list<ScoreRecord>::iterator s;
    for( s = mScores.begin(); s != mScores.end(); ++s )
    {
        /*  Render the score textures */
        r = get_render_rect( mScoreTextures[ texCount ], texCount );
        mScoreTextures[ texCount ]->render( r.x, r.y, r.w, r.h );
        ++texCount;

        /*  If the score being rendered is the current one, display 'new' */
        if( s->score == currentScore && mNew )
        {
            mNewText->set_position( r.x - 100, r.y + 4 );
            mNewText->render_flashing();
        }
    }


    /*  Render the bottom textures relative to the above populated rect */
    mHallOfFameInfo1->set_position(
            ( BWIDTH - mHallOfFameInfo1->get_width() ) / 2,
            r.y + 80 );

    mHallOfFameInfo2->set_position(
            ( BWIDTH - mHallOfFameInfo2->get_width() ) / 2,
            r.y + 110 );

    /*  Render those bad boys */
    mHallOfFameInfo1->render_self();
    mHallOfFameInfo2->render_self();
}




/*
--------------------------------------------------------------------------------
                                GET RENDER RECT
--------------------------------------------------------------------------------
 *  This gets a draw rect according to the texture and a given 'step', which is
 *  an index inside a for loop; this is used to adjust the position of the rect.
*/
SDL_Rect Scores::get_render_rect( Texture *texture, int step )
{
    /*  Create the rect */
    SDL_Rect r = {
        ( BWIDTH - mScoreTextures[ 0 ]->get_width() ) / 2,
        (40 * step) + 200,
        mScoreTextures[ step ]->get_width(),
        mScoreTextures[ step ]->get_height() };

    return( r );
}



/*
--------------------------------------------------------------------------------
                                 RENDER HEADER
--------------------------------------------------------------------------------
 *  This renders the top text in the high scores screen.
*/
void Scores::render_header( void )
{
    /*  Set positions */
    mHallOfFameText->set_position(
            ( BWIDTH - mHallOfFameText->get_width() ) / 2, 60 );

    mHallOfFameTextWhite->set_position(
            ( BWIDTH - mHallOfFameText->get_width() ) / 2, 60 );


    /*  Render the two textures, the second pulsing over the first */
    render_pulse( mHallOfFameText, mHallOfFameTextWhite, 4 );

}


/*
--------------------------------------------------------------------------------
                              SET / GET FILE PATH
--------------------------------------------------------------------------------
*/
void Scores::set_file_path( const char *path )
{
    mFilePath = path;
}


const char* Scores::get_file_path( void )
{
    return( mFilePath.c_str() );
}



/*
--------------------------------------------------------------------------------
                                SCORE QUALIFIES
--------------------------------------------------------------------------------
 *  Checks to see if the given score (basically always the current player score)
 *  qualifies to be in the top ten scores
*/
bool Scores::score_qualifies( Uint32 nScore )
{
    /*  We default to no */
    bool qualifies = false;

    /*
     *  Iterate through the list of scores and compare the given score against
     *  each one of them; if it's higher than at least one of them, it qualifies
     */
    std::list<ScoreRecord>::iterator s;
    for( s = mScores.begin(); s != mScores.end(); ++s )
    {
        if( nScore > s->score )
        {
            qualifies = true;
            break;
        }
    }

    /*  Return either the success or failure of the 'qualifies' check */
    return( qualifies );
}


/*
--------------------------------------------------------------------------------
                                   ADD SCORE
--------------------------------------------------------------------------------
 *  Add a new score into the top ten, then sort and resize the list strip any
 *  sign of weakness from the Hall of Fame
*/
void Scores::add_score( Uint32 nScore, char *nInitials )
{
    /*  Create a new record */
    struct ScoreRecord record;

    /*  Set the record's score to that of the player's */
    record.score = nScore;

    /*  Set the initials for the record */
    record.initials[ 0 ] = nInitials[ 0 ];
    record.initials[ 1 ] = nInitials[ 1 ];
    record.initials[ 2 ] = nInitials[ 2 ];
    record.initials[ 3 ] = '\0';

    /*  Push the record onto the list */
    mScores.push_back( record );

    /*  Reorganize the list */
    mScores.sort( compare_scores );
    mScores.reverse();

    /*  Cut off any scores that didn't make the top 10 */
    if( mScores.size() > (unsigned int) mScoresToKeep )
        mScores.resize( mScoresToKeep );
}



/*
--------------------------------------------------------------------------------
                                 SET FILE PATHS
--------------------------------------------------------------------------------
*/
void Scores::set_dat_file_path( const char *path )
{
    mFilePath.assign( path );
}

void Scores::set_txt_file_path( const char *path )
{
    mFileTextPath.assign( path );
}



/*
--------------------------------------------------------------------------------
                                 SET / GET NEW
--------------------------------------------------------------------------------
*/
void Scores::set_new( bool newness )
{
    mNew = newness;
}


bool Scores::get_new( void )
{
    return( mNew );
}
