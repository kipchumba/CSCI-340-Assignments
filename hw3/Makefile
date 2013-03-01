

# the compiler in use
CC=g++

# options to pass to the compiler
CFLAGS= -c -Wall

# default target

ExprTree.o: ExprTree.h ExprTree.cpp 
		$(CC) $(CFLAGS) ExprTree.h ExprTree.cpp 
		
Variable.o: Variable.h Variable.cpp
		$(CC) $(CFLAGS) Variable.h Variable.cpp
		
TNode.o: TNode.h TNode.cpp
		$(CC) $(CFLAGS) TNode.h TNode.cpp

clean: 
		rm -rf *o *h.gch hw3.exe