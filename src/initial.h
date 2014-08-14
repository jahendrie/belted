/*******************************************************************************
 *  initial.h
 *
 *  This is the header file for the initial class.

*******************************************************************************/
#ifndef CLASS_INITIAL_H
#define CLASS_INITIAL_H

/*
 *  The initial class
 */
class Initial
{
    public:
        /*  Constructor */
        Initial( void );

        /*  Destructor */
        ~Initial( void );

        /*  Init function */
        bool init( void );

        /*  Free texture */
        void free_texture( void );

        /*  Set the letter */
        void set_letter( char letter );

        /*  Get the letter */
        char get_letter( void );

        /*  Increment current letter */
        void letter_up( void );

        /*  Decrement current letter */
        void letter_down( void );

        /*  Flash stuff */
        void set_flashing( bool flashing );
        bool is_flashing( void );

        /*  Focus stuff */
        void set_focus( bool focus );
        bool has_focus( void );

        /*  Create / update the letter texture */
        bool create_letter_texture( void );
        void update_letter_texture( void );

        /*  Flash ticks stuff */
        void set_flash_ticks( int ticks );
        void set_max_flash_ticks( int ticks );
        int get_flash_ticks( void );
        int get_max_flash_ticks( void );
        int get_max_flash_ticks_default( void );

        /*  Get the texture object */
        Texture* get_texture_object( void );

    private:
        /*  The texture object tied to this initial */
        Texture *mTextureObject;

        /*  The actual letter */
        char mLetter;

        /*  Flashing / focus bools */
        bool mFlashing;
        bool mHasFocus;
};

#endif
