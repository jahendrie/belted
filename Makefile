CC=g++
#CFLAGS=-g -Wall
CFLAGS=-O3
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OUTPUT=belted
FILES=src/close.cpp src/enemy.cpp src/events.cpp src/init.cpp src/load.cpp \
	  src/main.cpp src/player.cpp src/render.cpp src/ship.cpp src/texture.cpp \
	  src/update.cpp src/collision.cpp src/panel.cpp src/starfield.cpp \
	  src/atariExplosion.cpp src/warp.cpp src/tail.cpp src/border.cpp \
	  src/transition.cpp src/reset.cpp src/scores.cpp src/gameover.cpp \
	  src/initial.cpp src/enterhighscore.cpp src/help.cpp src/credits.cpp \
	  src/menu.cpp src/sounds.cpp src/args.cpp src/osd.cpp src/util.cpp\
	  src/kisskill.cpp

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(OUTPUT) $(LDFLAGS)
