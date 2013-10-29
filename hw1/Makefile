
# the compiler in use
CC=g++

# options to pass to the compiler
CFLAGS= -Wall -c -g

all:  hw1

hw1: BaseballPlayer.o Pitcher.o Hitter.o PlayerDatabase.o hw1.cpp 
		export GLIBCXX_FORCE_NEW=1
		$(CC) BaseballPlayer.o Pitcher.o Hitter.o PlayerDatabase.o hw1.cpp -o hw1

BaseballPlayer.o: BaseballPlayer.h BaseballPlayer.cpp 
		$(CC) $(CFLAGS) BaseballPlayer.h BaseballPlayer.cpp

Pitcher.o: Pitcher.h Pitcher.cpp
		$(CC) $(CFLAGS) Pitcher.h Pitcher.cpp

Hitter.o: Hitter.h Hitter.cpp
		$(CC) $(CFLAGS) Hitter.h Hitter.cpp

PlayerDatabase.o: PlayerDatabase.h PlayerDatabase.cpp
		$(CC) $(CFLAGS) PlayerDatabase.h PlayerDatabase.cpp 	
		
clean: 
		rm -f *.o *.gch *.exe
		