

# the compiler in use
CC=g++

# options to pass to the compiler
CFLAGS= -c -Wall -std=c++11

# default target
all: hw6
	
hw6: hw6.o 
		$(CC) hw6.o -o hw6

hw6.o: hw6.cpp heapsort.h scramble.h
		$(CC) $(CFLAGS) hw6.cpp heapsort.h scramble.h
clean: 
		rm -rf *o *h.gch hw6.exe
		