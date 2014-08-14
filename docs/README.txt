================================================================================
    belted      |   version 0.92    |   zlib license            |   2014-07-07
    James Hendrie                   |   hendrie.james@gmail.com
================================================================================

    1.  Description
    2.  Requirements / Restrictions
    3.  Installation / Uninstallation
    4.  Usage
    5.  Controls
    6.  Credits, etc.
    7.  Links



----------------------------------------
    1.  Description
----------------------------------------

    Belted is a game where you dodge asteroids in your spacecar.  Said spacecar
    is controlled with the mouse; you can use the keyboard if you want but it
    isn't recommended.



----------------------------------------
    2.  Requirements / Restrictions
----------------------------------------

    This game requires SDL2, SDL2_image, SDL2_mixer and SDL2_ttf to run or
    compile.  In addition, it requires a system (and drivers) capable of proper
    3D acceleration.

    To build this game, in addition to all of the SDL2 headers and libraries,
    you'll need a compiler and the standard C and C++ libraries and headers.  If
    you're able to compile anything at all you probably have these already.



----------------------------------------
    3.  Installation / Uninstallation
----------------------------------------

    To build, compile the program with 'make'.  It shouldn't take long, though
    obviously you'll need a C++ compiler.  If you're on any modern UNIX or Linux
    distro you should already have one, and if you don't, shame on you.  Go
    install GCC (gcc.gnu.org) right away.

    Currently, there is no actual 'installation' method for the program.  To run
    it, simply execute the binary from the directory in which it was built.


    Alternately, there do exist installers for both Windows and GNU/Linux
    (32-bit).  You can run one of those to install the game to a local
    directory, though you'll still need to execute the binary from its
    installation directory.  A shortcut takes care of this for the Windows
    install, and the linux installer can generate a shell script to execute the
    program to $HOME/bin if you'd like.



----------------------------------------
    4.  Usage
----------------------------------------

    Usage:  belted [OPTION]

    Options:
        -h or --help:		    Print help text
        -v or --version:	    Print version and author info
        -c or --controls:	    Print a comprehensive list of controls
        -s or --scores:	        Print the hall of fame to your terminal
        -l or --limit-fps:	    Limit FPS to 60, disable vsync
        -m or --mute:		    Start with music and sound muted
        -S or --story:	        Print the backstory to your terminal



----------------------------------------
    5.  Controls
----------------------------------------

    Mouse controls
        Move the mouse to move your ship
        Left click to honk or progress through screens
        Right click to activate power or go back through screens
        Scroll the mouse wheel to select menu entries
        Click the mouse wheel to bring the menu up or down

    Keyboard controls
        Use the ARROW KEYS to move the ship or navigate the menu
        Press SPACE to honk at asteroids or progress through screens
        Press SHIFT to activate your special charge power
        Press ESCAPE to go back through screens
        Press 'S' to toggle sounds
        Press 'M' to toggle music
        Press 'Q' to quit

    Also, pressing 'G' during play or in the main menu will toggle
    mouse grabbing.



----------------------------------------
    6.  Credits, etc.
----------------------------------------

    Programming, art:
        James Hendrie

    Music:
        Kevin MacLeod

    For more detailed credits information, including licenses, see the
    CREDITS.txt file.



----------------------------------------
    7.  Links
----------------------------------------

    Games page (personal site):
        http://www.someplacedumb.net/games
