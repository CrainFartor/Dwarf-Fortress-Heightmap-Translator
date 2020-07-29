CC=g++
CFLAGS= -Wall
LIBS=./lib/lib.cpp ./lib/EasyBMP.cpp ./lib/dat.cpp
MAIN=./src/main.cpp
EXE=DFHM

MAIN_LEGACY=./src/main_legacy.cpp
LIBS_LEGACY=./lib/lib_legacy.cpp ./lib/EasyBMP.cpp ./lib/dat_legacy.cpp
EXE_LEGACY=DFHM_Legacy

default: main

main:
	$(CC) $(CFLAGS) -o $(EXE) $(MAIN) $(LIBS)

clean:
	rm -f $(EXE)

legacy:
	$(CC) $(CFLAGS) -o $(EXE_LEGACY) $(MAIN_LEGACY) $(LIBS_LEGACY)

all: clean main
