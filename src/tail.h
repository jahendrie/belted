/*******************************************************************************
 *  tail.h
 *
 *  This is the header file for the tail class, defined in tail.cpp.
 *
*******************************************************************************/
#ifndef CLASS_TAIL_H
#define CLASS_TAIL_H

/*
 *  The Tail class
 */
class Tail
{
    public:
        /*  Constructor */
        Tail( void );

        /*  Destructor */
        ~Tail( void );

        /*  Generic clear / init function */
        void init_tail( void );

        /*  Update the tail */
        void update( void );

        /*  Render */
        void render( void );

        /*  Is this tail active? */
        void set_active( bool active );
        bool is_active( void );

        /*  Start or stop the tail, unambiguously */
        void start_tail( void );
        void start_fading( void );
        void stop_tail( void );

        /*  Lets the outside world know if the tail is empty of particles */
        bool is_fading( void );

    private:
        /*  Whether or not to keep updating the tail */
        bool mActive;
        bool mFading;

        /*  Position at which to render the tail */
        SDL_Point mPos;
};

#endif
