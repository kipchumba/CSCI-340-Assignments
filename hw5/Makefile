

# the compiler in use
CC=g++

# options to pass to the compiler
CFLAGS= -c -Wall

# default target
all: hw5
	
hw5: hw5.o 
		$(CC) hw5.o -o hw5

hw5.o: hw5.cpp HashTable.h StringHash.cpp
		$(CC) $(CFLAGS) hw5.cpp HashTable.h StringHash.cpp
clean: 
		rm -rf *o *h.gch hw5.exe
		