

# the compiler in use
CC=g++

# options to pass to the compiler
CFLAGS= -c -Wall

# default target
ALL: hw4

hw4: Table.o NumericTable.o hw4.o
		$(CC) Table.o NumericTable.o hw4.o -o hw4
		
hw4.o: Table.h NumericTable.h hw4.cpp
		$(CC) $(CFLAGS) Table.h NumericTable.h hw4.cpp
Table.o: Table.h Table.cpp 
		$(CC) $(CFLAGS) Table.h Table.cpp 
		
NumericTable.o: NumericTable.h NumericTable.cpp
		$(CC) $(CFLAGS) NumericTable.h NumericTable.cpp
		
clean: 
		rm -rf *o *h.gch 