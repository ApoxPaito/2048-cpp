CC=g++
LINK=g++
CFLAGS=-c -Wall -Iinclude

2048: OBJECT_FILES
	$(LINK) -static-libgcc -static-libstdc++ box.o gameboard.o main.o -o $@

OBJECT_FILES:
	$(CC) $(CFLAGS) box.cpp -o box.o
	$(CC) $(CFLAGS) gameboard.cpp -o gameboard.o
	$(CC) $(CFLAGS) main.cpp -o main.o