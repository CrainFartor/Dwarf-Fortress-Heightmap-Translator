CC=g++
CFLAGS= -Wall -Wno-write-strings
LIBS=./ver2/lib/lib.cpp ./EasyBMP/EasyBMP.cpp ./ver2/lib/dat.cpp ./ver2/lib/log.cpp ./ver2/lib/lmg.cpp
HEDS=./ver2/lib/lib.h ./EasyBMP/EasyBMP.h ./ver2/lib/dat.h ./ver2/lib/log.h ./ver2/lib/lmg.h ./ver2/def/def.h
OBJS=main.o lib.o EasyBMP.o dat.o log.o lmg.o

MAIN_LEGACY=./legacy/src/main_legacy.cpp
LIBS_LEGACY=./legacy/lib/lib_legacy.cpp ./legacy/lib/dat_legacy.cpp ./EasyBMP/EasyBMP.cpp

DFHM: $(OBJS) $(HEDS)
	$(CC) $(CFLAGS) -o DFHM $(OBJS)

main.o: ./ver2/src/main.cpp $(HEDS)
	$(CC) $(CFLAGS) -c ./ver2/src/main.cpp

lib.o: ./ver2/lib/lib.cpp $(HEDS)
	$(CC) $(CFLAGS) -c ./ver2/lib/lib.cpp

EasyBMP.o: ./EasyBMP/EasyBMP.cpp $(HEDS)
	$(CC) $(CFLAGS) -c ./EasyBMP/EasyBMP.cpp

dat.o: ./ver2/lib/dat.cpp $(HEDS)
	$(CC) $(CFLAGS) -c ./ver2/lib/dat.cpp

log.o: ./ver2/lib/log.cpp $(HEDS)
	$(CC) $(CFLAGS) -c ./ver2/lib/log.cpp

lmg.o: ./ver2/lib/lmg.cpp $(HEDS)
	$(CC) $(CFLAGS) -c ./ver2/lib/lmg.cpp

clean:
	rm -f DFHM
	rm -f *.o

DFHM_Legacy: $(MAIN_LEGACY) $(LIBS_LEGACY)
	$(CC) $(CFLAGS) -o DFHM_Legacy $(MAIN_LEGACY) $(LIBS_LEGACY)

all: clean DFHM
