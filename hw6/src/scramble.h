#ifndef SCRAMBLE_H
#define SCRAMBLE_H

#include <ctime>
#include <cstdlib>
#include <vector>

template <class T>
void scramble (std::vector<T>& vector_to_scramble) {
	
	srand (time (0) );
	int size=vector_to_scramble.size();
	
	for ( int i=0; i<(size/2); i++ ) {
		int right= rand()%size;
		int left= rand()%size;
		
		if (left!=right){
		
			std::swap (vector_to_scramble[left],vector_to_scramble[right]);
		}
		
	}
	
}

#endif