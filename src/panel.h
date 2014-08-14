/*******************************************************************************
 *  panel.h
 *
 *  This is the header file for the panel class, defined in panel.cpp.
 *
*******************************************************************************/
#ifndef CLASS_PANEL_H
#define CLASS_PANEL_H


/*
 *  Enum for clipping rects
 */
enum panelClippingRectNums
{
    CLIP_CORNER_TOP_LEFT,
    CLIP_CORNER_TOP_RIGHT,
    CLIP_CORNER_BOTTOM_RIGHT,
    CLIP_CORNER_BOTTOM_LEFT,
    CLIP_BORDER_LEFT,
    CLIP_BORDER_RIGHT,
    CLIP_BORDER_TOP,
    CLIP_BORDER_BOTTOM,
    CLIP_MIDDLE,
    PANEL_TEXTURE_CLIPS
};

enum panelButtonsEnum
{
    BUTTON_OFF,
    BUTTON_CHARGING,
    BUTTON_ON,
    TOTAL_PANEL_BUTTONS
};

/*
 *  The stats panel
 */
class Panel
{
    public:
        /*  Constructor */
        Panel( void );

        /*  Destructor */
        ~Panel( void );

        /*  Initialize the texture clipping array */
        void init_clips( void );

        /*  Lay out the panel */
        void init_layout( void );
        void layout( void );

        /*  Set / get dimensions */
        void set_width( int width );
        void set_height( int height );
        int get_width( void );
        int get_height( void );

        /*  Set / get position */
        void set_position( int x, int y );
        int get_pos_x( void );
        int get_pos_y( void );

        /*  Quick and dirty rect initialization */
        void set_rect( int x, int y );

        /*  Set texture object */
        void set_panel_texture_background( Texture *texture );
        void set_panel_texture_buttons( Texture *texture );
        void set_score_texture_object( Texture *texture );
        void set_high_score_texture_object( Texture *texture );

        /*  Render */
        void render( void );


    private:
        /*  Panel object position */
        SDL_Point mPos;

        /*  Panel object dimensions */
        int mWidth;
        int mHeight;

        /*  Relative positions of various panel objects */
        SDL_Point mScorePos;
        SDL_Point mHighScorePos;

        /*  Clip rects */
        SDL_Rect mClips[ PANEL_TEXTURE_CLIPS ];
        SDL_Rect mButtonClips[ TOTAL_PANEL_BUTTONS ];

        /*  The current draw rect */
        SDL_Rect mDrawRect;

        /*  The texture object pointers */
        Texture *mTextureBackground;
        Texture *mTextureButtons;
        Texture *mScoreTexture;
        Texture *mHighScoreTexture;
};

#endif
