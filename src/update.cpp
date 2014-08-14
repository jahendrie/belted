/*******************************************************************************
 *  update.cpp
 *
 *  This file defines the functions that handle all of the updating in the game,
 *  such as moving the player's ship, the enemies, updating starfield positions,
 *  etc.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  UPDATE MAIN
--------------------------------------------------------------------------------
 *  This function updates stuff on the main screen (during gameplay).
*/
void update_main( void )
{
    /*  Warp speed update */
    if( warp )
        warp_update();

    /*  Tail update */
    if( tail.is_active() || tail.is_fading() )
    {
        tail.update();
    }

    /*  Add a few enemies */
    if( enemyDelay >= 120 )
    {
        /*
         *  Every tick (60 per second by default), there is a one in
         *  (15 * warpSpeed) chance that the program will 'consider' spawning
         *  an enemy.
         */
        for( int i = 0; i < ( rand() % ( 15 * warpSpeed ) ) + 1; ++i )
        {
            /*  If the player is is not powered, 1/80 chance of an enemy */
            if( ! player.is_powered() )
            {
                if( rand() % 80 == 0 )
                    load_enemy();
            }

            /*  If they are powered, 1/40 chance (more enemies) */
            else
            {
                if( rand() % 40 == 0 )
                    load_enemy();
            }
        }
    }

    /*  Tilt the player's ship according to movement */
    player.tilt();

    /*  Get the player's general area/position */
    SDL_Rect pRect = player.get_rect();

    /*  Update the enemies */
    if( enemies.size() > 0 )
    {
        /*  Create the enemies vector iterator */
        std::vector<Enemy>::iterator enemy;

        /*  Update the enemies */
        for( enemy = enemies.begin(); enemy != enemies.end(); )
        {
            /*  Update the enemy (movement, etc.) */
            enemy->update();

            /*  Get the enemy's general rectangle */
            SDL_Rect eRect = enemy->get_rect();      //  lololol erect

            /*  If the player and enemy are in very close proximity */
            if( check_collision_box( pRect, eRect ) )
            {
                /*  If the player honks at the asteroid */
                if( player.is_honking() )
                    enemy->kiss();

                /*  Grab the player's colliders vector */
                std::vector<Collider> pCollider = player.get_pixel_collider(
                        player.get_current_frame() );
                
                /*  Grab this enemy's colliders vector */
                std::vector<Collider> eCollider = enemy->get_pixel_collider(
                        enemy->get_current_frame() );


                /*  Check for collision between the sets of colliders */
                if( check_collision_colliders( pCollider, eCollider ) )
                {
                    /*  If the player is powered up, destroy the enemy */
                    if( player.is_powered() )
                        enemy->kill();

                    //  Otherwise, under normal circumstances, kill the player
                    else if( player.is_alive() &&
                            enemy->is_alive() &&
                            ! player.is_invulnerable() )
                    {
                        player.kill();
                    }
                }
            }

            /*  If the enemy has gone beyond the visible play area, erase it */
            if( enemy->get_pos_y() > BHEIGHT )
                enemies.erase( enemy );

            /*  If the enemy is dead and gone, erase it */
            else if( ! enemy->is_alive() && ! enemy->is_exploding() )
                enemies.erase( enemy );

            /*  Otherwise, move on to the next enemy in the vector */
            else
                ++enemy;
        }
    }


    /*  If the player is alive and doesn't have respawn invuln */
    if( player.is_alive() && 
            ( player.is_powered() || ! player.is_invulnerable() ) )
    {
        /*  Update the main score */
        if( currentScore < 1e10 )   //  Max score:  999,999,999
            ++currentScore;

        /*  Update the other score trackers */
        if( ! player.is_powered() && chargeScore < 1e10 )
            ++chargeScore;
        if( extraLifeScore < 1e10 )
            ++extraLifeScore;

        /*  Update the player's charge meter */
        if( chargeScore >= 1000 )
        {
            player.increment_charge();
            chargeScore -= 1000;
        }

        /*  If the player has enough points, increase life */
        if( extraLifeScore >= 20000 )
        {
            player.increment_lives();
            extraLifeScore -= 20000;
        }
    }

    /*  If applicable, update player power status */
    if( player.is_powered() )
        player.power_update();

    /*  Update score string and texture */
    snprintf( currentScoreString, 9, "%06d", currentScore );
    scoreText->create_texture_from_string( gFontTiny, currentScoreString,
            colors[ COLOR_WHITE ] );

    /*  Wait a couple of seconds before spawning enemies */
    if( enemyDelay < 121 )
        ++enemyDelay;

    /*  Update the starfield */
    starfield->update();

    /*  The player update function - just controls the honk, really */
    player.update();

    /*  Create an iterator for the 'atari' explosions vector */
    std::vector<AtariExplosion>::iterator a;

    /*  Iterate through the vector */
    for( a = aExplosions.begin(); a != aExplosions.end(); )
    {
        /*  Erase the ones that are dead */
        if( a->is_done() )
            aExplosions.erase( a );

        /*  Update the ones that aren't, then move on */
        else
        {
            a->update( player.get_special_color() );
            ++a;
        }
    }

    /*  We do this here so that the pause menu will display the correct text */
    if( gamePaused )
        gamePaused = false;

    /*  If the OSD isn't null, update it */
    update_osd();

    /*  Update the kissKills object */
    kissKills.update();

}


/*
--------------------------------------------------------------------------------
                            UPDATE ENTER HIGH SCORE
--------------------------------------------------------------------------------
 *  This updates everything on the 'enter high score' screen (pretty much just
 *  the initials).
*/
void update_enter_high_score( void )
{
    /*  Whichever one has focus, set to flashing */
    for( int i = 0; i < 3; ++i )
    {
        if( initials[ i ]->has_focus() )
            initials[ i ]->set_flashing( true );
        else
            initials[ i ]->set_flashing( false );
    }
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Master update function; this determines which of the other update functions
 *  to call based on the current screen.
*/
void update( void )
{
    if( currentScreen == SCREEN_MAIN )
        update_main();
    else if( currentScreen == SCREEN_ENTER_HIGH_SCORE )
        update_enter_high_score();
}
