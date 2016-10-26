INSTALL	= /usr/bin/env install
AR	= /usr/bin/env ar
ARFLAGS	= rcs
DEST	=
PREFIX	=
CC	= g++
BINDIR	=
TARGET	= test_display test_window
LINK	= g++
CFLAGS	= -std=c++11 -O2 -Wall -Wextra -static
LFLAGS	=
LIBS	= -lkuma `pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer lua5.3 yaml-cpp` 
INCDIR	= -I../src -Icatch `pkg-config --cflags sdl2 lua5.3` -I/usr/include/yaml-cpp
LIBDIR	= -L../
CLEAN	=
DEL	= rm -f
SRC	= src/test_display.cpp \
	  src/test_window.cpp
OBJ	= src/test_display.o \
	  src/test_window.o

first: all

.PHONY: doc clean

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CC) -c $(CFLAGS) $(INCDIR) -o "$@" "$<"

.cc.o:
	$(CC) -c $(CFLAGS) $(INCDIR) -o "$@" "$<"

.cxx.o:
	$(CC) -c $(CFLAGS) $(INCDIR) -o "$@" "$<"

.C.o:
	$(CC) -c $(CFLAGS) $(INCDIR) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCDIR) -o "$@" "$<"

all: test_display test_window

test_display: $(OBJ)
	$(CC) $(LFLAGS) -o test_display $(OBJ) $(LIBDIR) $(LIBS)

test_window: $(OBJ)
	$(CC) $(LFLAGS) -o test_window $(OBJ) $(LIBDIR) $(LIBS)

src/test_display.o: src/test_display.cpp
	$(CC) -c $(CFLAGS) $(INCDIR) -o src/test_display.o src/test_display.cpp

src/test_window.o: src/test_window.cpp
	$(CC) -c $(CFLAGS) $(INCDIR) -o src/test_window.o src/test_window.cpp


clean:
	$(DEL) $(OBJ)
	$(DEL) test_display test_window
	$(DEL) 
doc:
	valgrind ./test_window
	valgrind ./test_display
