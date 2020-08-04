CountPixels: main.o EasyBMP.o lib.o
	g++ -Wall -o CountPixels main.o lib.o EasyBMP.o

main.o: ./src/main.cpp ./def/def.h
	g++ -Wall -c ./src/main.cpp

lib.o: ./lib/lib.cpp ./lib/lib.h
	g++ -Wall -c ./lib/lib.cpp

EasyBMP.o: ./lib/EasyBMP/EasyBMP.cpp
	g++ -Wall -c ./lib/EasyBMP/EasyBMP.cpp
