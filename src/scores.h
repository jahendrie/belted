/*******************************************************************************
 *  scores.h
 *
 *  This is the header file for the scores class, defined in scores.cpp.
 *
*******************************************************************************/
#ifndef CLASS_SCORES_H
#define CLASS_SCORES_H

/*
 *  The scores class
 */
class Scores
{
    public:
        /*  Constructor */
        Scores( void );

        /*  Destructor */
        ~Scores( void );

        /*  Free the textures */
        void free_textures( void );

        /*  Set / get current score file path */
        void set_file_path( const char *path );
        const char* get_file_path( void );

        /*  Init stuff */
        bool init( void );
        bool create_score_textures( void );

        /*  Reading and writing the scores */
        bool open_file( const char *path, const char *mode );
        void read_scores( const char *path );
        void write_scores( void );
        void write_scores_dat( const char *path );
        void write_scores_txt( const char *path );

        /*  Update function */
        void update( void );

        /*  Render all of the current score textures */
        void render( void );
        void render_header( void );
        SDL_Rect get_render_rect( Texture *texture, int step );

        /*  See if the player's score qualifies */
        bool score_qualifies( Uint32 nScore );

        /*  Add a score to the top 10 (or top howevermany) */
        void add_score( Uint32 nScore, char *nInitials );

        /*  Set file paths */
        void set_dat_file_path( const char *path );
        void set_txt_file_path( const char *path );

        /*  Set / get new status */
        void set_new( bool newness );
        bool get_new( void );

    private:
        /*  The highest score ever recorded */
        unsigned int mHighScore;

        /*  Number of scores to keep */
        int mScoresToKeep;

        /*  File stuff */
        FILE *mScoreFile;
        std::string mFilePath;
        std::string mFileTextPath;

        /*  Vector of scores read from / written to score file */
        std::list<ScoreRecord> mScores;

        /*  Vector of score textures */
        std::vector<Texture*> mScoreTextures;

        /*  'new' text texture */
        Texture *mNewText;
        bool mNew;          //  Whether or not there's a new score

        /*  'Hall of fame' text textures */
        Texture *mHallOfFameText;
        Texture *mHallOfFameTextWhite;
        Texture *mHallOfFameInfo1;
        Texture *mHallOfFameInfo2;
};

#endif
