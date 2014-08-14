/*******************************************************************************
 *  player.h
 *
 *  This is the header file for the player class (defined in player.cpp), which
 *  inherits from the ship class (defined in ship.cpp).
 *
*******************************************************************************/
#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

/*
 *  The Player class, which inherits from the Ship class
 */
class Player : public Ship
{
    public:
        /*  Init player attributes */
        void init_player( void );
        void init_player_stats( void );
        void reset_stats( void );

        /*  Set / get lives */
        void increment_lives( void );

        /*  Set / get charge */
        void set_charge( int charge );
        int get_charge( void );
        bool is_charged( void );
        void increment_charge( void );

        /*  Move the player's ship to where the mouse is */
        void move_mouse( void );

        /*  Move player's ship using keyboard controls */
        void move_keyboard( void );

        /*  Movement according to velocity */
        void move_velocity( void );

        /*  Check boundaries (walls of play area) */
        void check_bounds( void );

        /*  Update the player */
        void update( void );

        /*  Render function */
        void render( void );
        void render_alive( void );
        void render_invulnerable( void );

        /*  Kill the player */
        void kill( void );

        /*  Invulerability stuff */
        bool is_invulnerable( void );
        void set_invulnerable( bool invulnerable );

        /*  Moving left / right */
        void tilt( void );

        /*  Set special texture */
        void set_special_texture_object( Texture *texture );

        /*  Power functions */
        void init_power( void );
        void end_power( void );
        bool is_powered( void );
        void power_update( void );

        /*  Get / set current color */
        void set_special_color( SDL_Color *color );
        SDL_Color* get_special_color( void );

        /*  Honking stuff */
        void honk( void );
        bool is_honking( void );

    private:
        /*  Number of lives */
        int mMaxLives;

        /*  Amount of charge */
        int mCharge;
        int mMaxCharge;
        bool mChargeFull;

        /*  Invulnerability */
        int mInvulnerableTicks;

        /*  Power stuff */
        bool mPowered;
        bool mPoweringDown;
        int mPowerTicks;
        int mPowerMaxTicks;

        /*  Special texture object */
        Texture *mNormalTextureObject;
        Texture *mSpecialTextureObject;

        /*  Pointer to the current color */
        SDL_Color *mCurrentColor;

        /*  Channel for the various sound effects */
        int mChannel;

        /*  Is the player currently honking? */
        bool mHonking;

        /*  Player's velocity */
        SDL_Point mVelocity;
        int mMaxVelocity;
        int mMinVelocity;
        int mMidVelocity;
};

#endif
