/*******************************************************************************
 *  starfield.h
 *
 *  This is the header file for the starfield object, defined in starfield.cpp.
*******************************************************************************/
#ifndef CLASS_STARFIELD_H
#define CLASS_STARFIELD_H

struct Star
{
    SDL_Point pos;          //  Position of star
    SDL_Color color;        //  Color
    bool twinkle;           //  Whether or not it twinkles
    int alphaMin;           //  Minimum alpha value
};

/*
 *  The Starfield class
 */
class Starfield
{
    public:
        /*  Constructor */
        Starfield( void );

        /*  Destructor */
        ~Starfield( void );

        /*  Add a star */
        void add_star( int x, int y );

        /*  Update */
        void update( void );

        /*  Render */
        void render( void );
        void render_normal( void );
        void render_warp( void );

    private:
        /*  The collection of star structs */
        std::vector<Star> mStars;
        std::vector<Star>::iterator mStar;      //  Iterator
};

#endif
