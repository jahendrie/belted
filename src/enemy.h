/*******************************************************************************
 *  enemy.h
 *
 *  Header file for the Enemy class, which inherits from the Ship class.
 *
*******************************************************************************/
#ifndef CLASS_ENEMY_H
#define CLASS_ENEMY_H

/*
 *  The enemy class, which inherits from the Ship class
 */
class Enemy : public Ship
{
    public:
        /*  Init the enemy's attributes */
        void init_enemy( void );
        void init_point_values( int scale, int velocity );

        /*  Set / get the velocity (up/down speed) */
        void set_velocity( int velocity );
        int get_velocity( void );

        /*  Set / get direction ( -1 = up, 1 = down ) */
        void set_direction( int direction );
        int get_direction( void );
        void flip_direction( void );

        /*  Move the ship */
        void move( void );

        /*  Update function */
        void update( void );

        /*  Kiss the enemy */
        void kiss( void );

        /*  Destroy the enemy */
        void kill( void );

        /*  Make live / check if alive */
        void live( void );
        bool is_alive( void );

    private:
        /*  Velocity of this bad guy */
        int mVelocity;

        /*  Direction the bad guy's moving */
        int mDirection;

        /*  Whether or not the player 'kissed' this enemy */
        bool mKissed;

        /*  The point values for this enemy */
        int mPointsKilled;
        int mPointsKissed;
};

#endif
