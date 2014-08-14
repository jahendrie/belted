/*******************************************************************************
 *  menu.h
 *
 *  This is the header file for the main menu class defined in menu.cpp.
 *
*******************************************************************************/
#ifndef CLASS_MENU_H
#define CLASS_MENU_H


enum menuSelectionEnum
{
    SELECTION_START,            //  "START"
    SELECTION_RESUME,           //  "RESUME"
    SELECTION_HOF,              //  "VIEW HIGH SCORES"
    SELECTION_HELP,             //  "HELP"
    SELECTION_CREDITS,          //  "CREDITS"
    SELECTION_QUIT,             //  "QUIT"
    TOTAL_SELECTIONS
};

struct menuSelection
{
    Texture *textureNormal;     //  Normal texture
    Texture *texturePulse;      //  Texture that pulses over the normal one
    bool pulse;                 //  Whether or not to pulse
    int num;                    //  Selection number of this selection
    bool activated;             //  Whether or not this selection is activated
};



/*
 *  The Menu screen
 */
class Menu
{
    public:
        /*  Constructor */
        Menu( void );

        /*  Destructor */
        ~Menu( void );

        /*  Free a given texture */
        void free_texture( Texture *texture );

        /*  Free the textures */
        void free_textures( void );

        /*  Create the texture objects */
        bool create_textures( void );

        /*  Init a given selection */
        bool init_selection( struct menuSelection &s, const char *string,
               SDL_Color color );

        /*  Init / create textures */
        bool init( void );

        /*  Lay out the textures */
        void layout( void );

        /*  Select */
        void select( int currentSelection );

        /*  Handle events */
        void handle_events( SDL_Event &e );

        /*  Render */
        void render_selection( struct menuSelection &s );
        void render( void );

    private:
        /*  Graphic */
        Texture *mGraphic;

        /*  Version text texture */
        Texture *mVersion;

        /*  Struct for our menu selection options */
        struct menuSelection selections[ TOTAL_SELECTIONS ];

};


#endif
