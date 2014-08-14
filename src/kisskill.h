/*******************************************************************************
 *  kisskill.h
 *
 *  This is the header file for the KissKill class, defined in kisskill.cpp.
 *
*******************************************************************************/
#ifndef CLASS_KISSKILL_H
#define CLASS_KISSKILL_H

struct kissKill
{
    Texture *texture;   //  Texture object pointer
    bool isActive;      //  Is this OSD still active?
};

/*
 *  The KissKill class
 */
class KissKill
{
    public:
        /*  Constructor */
        KissKill( void );

        /*  Destructor */
        ~KissKill( void );

        /*  Clear out the vector */
        void clear( void );

        /*  Add a new kiss/kill OSD */
        bool add( int x, int y, const char *string, SDL_Color &color );

        /*  Update function */
        void update( void );

        /*  Renders all of the kiss/kill texture objects */
        void render( void );

    private:
        /*  Store our kissKill structs */
        std::vector<kissKill> mKissKills;

};

#endif
