
# the compiler in use
CC=g++

# options to pass to the compiler
CFLAGS= -Wall -c 

all:  hw2

hw2: BaseballPlayer.o Pitcher.o Hitter.o PlayerDatabase.o create_names.o hw2.o 
		$(CC) BaseballPlayer.o Pitcher.o Hitter.o PlayerDatabase.o create_names.o hw2.o -o hw2

hw2.o: hw2.cpp PlayerDatabase.h
		$(CC) $(CFLAGS) hw2.cpp PlayerDatabase.h

BaseballPlayer.o: BaseballPlayer.h BaseballPlayer.cpp 
		$(CC) $(CFLAGS) BaseballPlayer.h BaseballPlayer.cpp

Pitcher.o: Pitcher.h Pitcher.cpp
		$(CC) $(CFLAGS) Pitcher.h Pitcher.cpp

Hitter.o: Hitter.h Hitter.cpp
		$(CC) $(CFLAGS) Hitter.h Hitter.cpp

PlayerDatabase.o: PlayerDatabase.h PlayerDatabase.cpp 
		$(CC) $(CFLAGS) -std=c++0x PlayerDatabase.h PlayerDatabase.cpp 
		
create_names.o: create_names.h create_names.cpp
		$(CC) $(CFLAGS)	create_names.h create_names.cpp

cppMemDbg.o: cppMemDbg.h cppMemDbg.cpp 
		$(CC) $(CFLAGS)	cppMemDbg.h cppMemDbg.cpp
clean: 
		rm -rf *o *.gch hw2.o
		