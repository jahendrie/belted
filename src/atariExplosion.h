/*******************************************************************************
 *  atariExplosion.h
 *
 *  Header file for the atariExplosion class, which is used to create colorful
 *  explosions when the player runs into enemies while powered.
 *
*******************************************************************************/
#ifndef CLASS_ATARI_EXPLOSION_H
#define CLASS_ATARI_EXPLOSION_H

struct ARect
{
    SDL_Point pos;          //  Current position
    SDL_Point target;       //  Target position
    SDL_Point velocity;     //  How fast this thingy moves
    int w;                  //  Width
    int h;                  //  Height
    Uint8 a;                //  Alpha value of rect
    bool done;              //  Is this rect done with?
};

/*
 *  The 'atari explosion' class
 */
class AtariExplosion
{
    public:
        /*  Constructor */
        AtariExplosion( void );

        /*  Destructor */
        ~AtariExplosion( void );

        /*  Init the explosion */
        void init( int x, int y, SDL_Color *color );

        /*  Render the explosion */
        void render( void );

        /*  Update the explosion */
        void update( SDL_Color *color = NULL );

        /*  Check if the explosion is all done */
        bool is_done( void );

    private:
        /*  The rects we'll use to draw the explosion */
        std::vector<ARect> mExplosionRects;

        /*  Pointer to the color we're drawing the rects with */
        SDL_Color *mColor;
};

#endif
