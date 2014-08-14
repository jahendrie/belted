/*******************************************************************************
 *  texture.h
 *
 *  This is the header file for the Texture class, defined in texture.cpp.
 *
*******************************************************************************/
#ifndef CLASS_TEXTURE_H
#define CLASS_TEXTURE_H

/*
 *  The texture class
 */
class Texture
{
    public:
        /*  Constructor */
        Texture( void );

        /*  Destructor */
        ~Texture( void );

        /*  Free texture memory */
        void free_texture( void );

        /*  Create a texture from a file */
        bool create_texture_from_file( const char *path, bool clipping = false,
                int cWidth = 0, int cHeight = 0, int cCount = 0 );

        /*  Create a texture from a string of text */
        bool create_texture_from_string( TTF_Font *font, const char *string,
                SDL_Color textColor );

        /*  Get default dimensions */
        int get_texture_width( void );
        int get_texture_height( void );

        /*  Get / set current dimensions */
        int get_width( void );
        int get_height( void );
        void set_width( int width );
        void set_height( int height );

        /*  Get / set current 'hard' position */
        void set_position( int x, int y );
        int get_pos_x( void );
        int get_pos_y( void );

        /*  Render the texture */
        void render_self( void );
        void render( int x, int y, int width, int height, SDL_Rect *clip =NULL);
        void render_ext( SDL_Rect *drawRect, SDL_Rect *clip );
        void render_fade( void );
        void render_flashing( void );

        /*  Modulate texture alpha */
        void mod_alpha( Uint8 alpha );

        /*  Set max frames */
        void set_max_frames( int frames );

        /*  Create colliders */
        void generate_colliders( SDL_Surface *surface, int size, int frame );

        /*  Get pixel collider */
        std::vector<Collider> get_pixel_collider( int frame );

        /*  Fade stuff */
        void set_fading( bool fade );
        bool is_fading( void );

        /*  Set / get alpha mod */
        Uint8 get_alpha( void );
        void set_alpha( Uint8 alpha );

        /*  Set / get color mod */
        void get_color_mod( Uint8 *r, Uint8 *g, Uint8 *b );
        void set_color_mod( Uint8 r, Uint8 g, Uint8 b );
        void save_color_mod( void );
        void restore_color_mod( void );

        /*  Flash stuff */
        void set_flashing( bool flashing );
        void set_flash_ticks( int ticks );
        void set_max_flash_ticks( int ticks );
        bool is_flashing( void );
        int get_flash_ticks( void );
        int get_max_flash_ticks( void );
        int get_max_flash_ticks_default( void );

        /*  Focus stuff */
        void set_focus( bool focus );
        bool has_focus( void );

    private:
        /*  Pointer to the texture data */
        SDL_Texture *mTexture;

        /*  Position of the texture */
        SDL_Point mPos;

        /*  Default (loaded) texture dimensions */
        int mTextureWidth;
        int mTextureHeight;

        /*  Currently set (scaled) dimensions */
        int mWidth;
        int mHeight;

        /*  Fade stuff */
        bool mFading;
        int mFadeTicks;

        /*  Flashing stuff */
        bool mFlashing;
        int mFlashTicks;
        int mMaxFlashTicks;
        int mMaxFlashTicksDefault;

        /*  Does this texture object have focus? */
        bool mHasFocus;

        /*  The original values for the color mod */
        SDL_Color mOriginalColorMod;

        /*  Colliders vector array */
        std::vector<Collider> mColliders[ 30 ];
};

#endif
