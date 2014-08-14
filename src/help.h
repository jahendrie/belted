#ifndef CLASS_HELP_H
#define CLASS_HELP_H


enum helpScreenTextureEnum
{
    H_TITLE,
    H_HONK1,
    H_HONK2,
    H_POWER1,
    H_POWER2,
    H_MOUSE,
    H_SS,
    TOTAL_HELP_SCREEN_TEXTURES
};



/*
 *  The help screen class
 */
class Help
{
    public:
        /*  Constructor */
        Help( void );

        /*  Destructor */
        ~Help( void );

        /*  Init help stuff */
        bool init( void );

        /*  Free the textures */
        void free_textures( void );

        /*  Create the textures */
        bool create_textures( void );

        /*  Lay out all the textures */
        void layout( void );

        /*  Render the screen */
        void render( void );

    private:
        /*  Our help screen textures */
        Texture *mHelpTextures[ TOTAL_HELP_SCREEN_TEXTURES ];

        /*  The color of the border */
        SDL_Color borderColor;

        /*  Which direction the border is 'pulsing' in */
        int borderPulse;
};

#endif
