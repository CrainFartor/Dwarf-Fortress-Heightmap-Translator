CC=g++
CFLAGS= -Wall
LIBS=./lib/lib.cpp ./lib/EasyBMP.cpp ./lib/dat.cpp
MAIN=./src/main.cpp
EXE=DFHM

default: main

main:
	$(CC) $(CFLAGS) -o $(EXE) $(MAIN) $(LIBS)

clean:
	rm -f $(EXE)

all: clean main
