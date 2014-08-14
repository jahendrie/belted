/*******************************************************************************
 *  ship.h
 *
 *  This is the header file for the ship class defined in ship.cpp.  The ship
 *  class is inherited by the player class defined in player.cpp, as well as the
 *  enemy class defined in enemy.cpp.
 *
*******************************************************************************/
#ifndef CLASS_SHIP_H
#define CLASS_SHIP_H


/*  Particle struct, used for all things debris particle */
struct Particle
{
    SDL_Point pos;
    SDL_Point end;
    SDL_Color color;
    SDL_Point direction;
    SDL_Point velocity;
    bool twinkle;
};

enum debrisEnum
{
    DEBRIS_WHITE,
    DEBRIS_COLOR,
    DEBRIS_YELLOW,
    DEBRIS_ORANGE,
    TOTAL_DEBRIS
};


/*
 *  The ship class, which is inherited by the Player and Enemy classes
 */
class Ship
{
    public:
        /*  Constructor */
        Ship( void );

        /*  Destructor */
        ~Ship( void );

        /*  Set texture object */
        void set_texture_object( Texture *texture );

        /*  Set / get dimensions */
        void set_width( int width );
        void set_height( int height );
        int get_width( void );
        int get_height( void );
        int get_texture_width( void );
        int get_texture_height( void );

        /*  Set / get position */
        void set_position( int x, int y );
        int get_pos_x( void );
        int get_pos_y( void );

        /*  Render */
        void render( void ); /*  Collider stuff */

        /*  Collider stuff */
        void init_colliders( void );
        void init_pixel_colliders( void );
        void init_collider_circ( int radius );
        void init_collider_rect( int width, int height );
        void adjust_colliders( void );
        Circle& get_collider_circ( void );
        SDL_Rect& get_collider_rect( void );
        void translate_colliders( int scale );
        std::vector<Collider> get_pixel_collider( int frame = 0 );

        /*  Get rect for current object */
        SDL_Rect get_rect( void );
        SDL_Rect get_collider_rect( int index, int frame = 0 );

        /*  Set / get current / max frames */
        void set_max_frames( int frames );
        void set_current_frame( int frame );
        int get_max_frames( void );
        int get_current_frame( void );

        /*  Set clips */
        void init_clips( int rows, int columns, int width, int height );
        void init_clips_vertical( int width, int height, int frames );

        /*  Explosion stuff */
        void init_explosion( void );
        bool is_exploding( void );
        void render_exploding( void );

        /*  Set / get player status */
        void set_player( bool isPlayer );
        bool is_player( void );

        /*  Draw colliders */
        //void draw_colliders( std::vector<Collider> colliders );
        //void draw_default_colliders( void );

        /*  Lives stuff */
        void set_max_lives( int lives );
        void set_default_lives( int lives );
        void set_lives( int lives );
        int get_default_lives( void );
        int get_lives( void );
        bool is_alive( void );

    protected:
        /*  A pointer to the texture object this ship will render */
        Texture *mTextureObject;

        /*  Colliders vector */
        Circle mColliderCircle;
        SDL_Rect mColliderRect;
        std::vector<Collider> mColliders[ 30 ];

        /*  Dimensions */
        int mWidth, mHeight;

        /*  Position */
        SDL_Point mPos;

        /*  Frames in animation, max clipping frames */
        int mMaxFrames;
        int mFrame;

        /*  Texture clips */
        SDL_Rect mClips[ 30 ];

        /*  Is the ship alive? */
        bool mAlive;
        int mLives;
        int mDefaultLives;
        int mMaxLives;
        bool mInvulnerable;

        /*  Is it exploding? */
        bool mExploding;

        /*  Debris particles */
        Particle mDebris[ TOTAL_DEBRIS ][100];

        /*  The number of particles we want to draw */
        int mParticlesToDraw;

        /*  Is this ship controlled by the player? */
        bool mPlayer;
};

#endif
