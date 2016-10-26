INSTALL	= /usr/bin/env install
AR	= /usr/bin/env ar
ARFLAGS	= rcs
DEST	=
PREFIX	=
CC	= g++
BINDIR	=
TARGET	= kuma
LINK	= g++
CFLAGS	= -std=c++11 -O0 -Wall -Wextra -g -D_DEBUG_
LFLAGS	=
LIBS	= `pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer lua5.3 yaml-cpp` 
INCDIR	= -Isrc `pkg-config --cflags sdl2 lua5.3` -I/usr/include/yaml-cpp
LIBDIR	= 
CLEAN	=
DEL	= rm -f
SRC	= ./src/animation.cpp \
	  ./src/audio/mixer.cpp \
	  ./src/audio/sound.cpp \
	  ./src/config.cpp \
	  ./src/display.cpp \
	  ./src/entity.cpp \
	  ./src/entity_manager.cpp \
	  ./src/entity_map.cpp \
	  ./src/flip.cpp \
	  ./src/game.cpp \
	  ./src/init.cpp \
	  ./src/key_input.cpp \
	  ./src/layer.cpp \
	  ./src/log.cpp \
	  ./src/main.cpp \
	  ./src/map.cpp \
	  ./src/player_entity.cpp \
	  ./src/point.cpp \
	  ./src/pointer.cpp \
	  ./src/rect.cpp \
	  ./src/rw.cpp \
	  ./src/scene.cpp \
	  ./src/scene_manager.cpp \
	  ./src/script_context.cpp \
	  ./src/sprite.cpp \
	  ./src/sprite_sheet.cpp \
	  ./src/text.cpp \
	  ./src/texture.cpp \
	  ./src/tile.cpp \
	  ./src/timer.cpp \
	  ./src/user_files.cpp \
	  ./src/util.cpp \
	  ./src/window.cpp
OBJ	= ./src/animation.o \
	  ./src/audio/mixer.o \
	  ./src/audio/sound.o \
	  ./src/config.o \
	  ./src/display.o \
	  ./src/entity.o \
	  ./src/entity_manager.o \
	  ./src/entity_map.o \
	  ./src/flip.o \
	  ./src/game.o \
	  ./src/init.o \
	  ./src/key_input.o \
	  ./src/layer.o \
	  ./src/log.o \
	  ./src/main.o \
	  ./src/map.o \
	  ./src/player_entity.o \
	  ./src/point.o \
	  ./src/pointer.o \
	  ./src/rect.o \
	  ./src/rw.o \
	  ./src/scene.o \
	  ./src/scene_manager.o \
	  ./src/script_context.o \
	  ./src/sprite.o \
	  ./src/sprite_sheet.o \
	  ./src/text.o \
	  ./src/texture.o \
	  ./src/tile.o \
	  ./src/timer.o \
	  ./src/user_files.o \
	  ./src/util.o \
	  ./src/window.o

first: all

.PHONY: doc clean

all: kuma

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJ) $(LIBDIR) $(LIBS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCDIR) -o $@ $<
clean:
	$(DEL) $(OBJ)
	$(DEL) kuma
	$(DEL) -r doc/html doc/latex
doc:
	doxygen doc/doxygen.conf
	cp doc/doxy-boot.js doc/html/
