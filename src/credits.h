/*******************************************************************************
 *  credits.h
 *
 *  This is the header file for the credits class (credits screen)
 *
*******************************************************************************/
#ifndef CLASS_CREDITS_H
#define CLASS_CREDITS_H

/*
 *  The credits screen
 */
class Credits
{
    public:
        /*  Constructor */
        Credits( void );

        /*  Destructor */
        ~Credits( void );

        /*  Free the textures */
        void free_textures( void );

        /*  Init / create textures */
        bool init( void );

        /*  Lay out the textures */
        void layout( void );

        /*  Render */
        void render( void );

    private:
        /*  Our textures */
        Texture *mAuthor;               //  Author's picture
        Texture *mAuthorNameYellow;     //  Author's name (yellow)
        Texture *mAuthorNameWhite;      //  Author's name (white)
        Texture *mAuthorEmail;          //  Author's email address
        Texture *mAuthorWebsite;        //  Author's website
        Texture *mMusic1;               //  Music credits line 1
        Texture *mMusic2;               //  Music credits line 2
        Texture *mCredits;              //  credits.txt text hint
};


#endif
