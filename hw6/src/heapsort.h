#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <iostream>
#include <vector>

// This function reads items from the input vector and builds a heap structure. 
// The first argument to this function is a reference to the input vector. 
// The second argument is a reference to a vector for storing the heap structure. 
// The last argument is a predicate (a Boolean function or class containing one) for case-independent ascending sort.
// The function iterates over the input vector, inserting them one at a time into the heap vector. 
// To insert an individual item into the heap, it calls the insert() function described below.

template <class T, class Pred>
void build_heap (std::vector<T>& input_vector, std::vector<T>& heap_vector, Pred pred){
	
	for (typename std::vector<T>::const_iterator iter=input_vector.begin(); iter!=input_vector.end(); ++iter) {
		insert (heap_vector,*iter,pred);
		//std::cout<<heap_vector.size()<<std::endl;
	}

}


// This function retrieves items from the heap structure and inserts them in sequence into the result vector. 
// The first argument to this function is a reference to a vector that contains the heap structure. 
// The second argument is a reference to a vector containing the sorted results. 
// The last argument is the same predicate as used earlier.
// The function should remove items from the heap and print them until only one item is left in the heap
// (the sentinel item that occupies the first vector position). 
// An individual item can be removed from the heap by calling the remove() function described below.

template <class T, class Pred>
void heapsort (std::vector<T>& heap_vector, std::vector<T>& sorted_vector, Pred pred){
	
	while (heap_vector.size()!=1){
		
		T temp = remove (heap_vector,pred);
		std::cout<<temp<<std::endl;
		sorted_vector.push_back(temp);
	}

}

// This function inserts an item (the second argument) into a heap (the first argument) with the given order (the third argument). 
// The item can be inserted at the back of the heap using the vector method push_back(). 
// After insertion, the function upheap() (see below) should be called to move the newly inserted item up the heap to its proper location.

template <class T, class Pred>
void insert (std::vector<T>& heap_vector, const T& item, Pred pred){
	
	heap_vector.push_back(item);
	upheap(heap_vector,heap_vector.size()-1,pred);
	
}

// This function is used to retrieve a single item from the heap structure (the first argument) with the given order (the second argument). 
// One possible implementation of this function's logic is as follows: 
// Swap the first, non-sentinel item in the heap with the last item in the heap. 
// Obtain the value of the last item in the heap using the vector method back() and save it to be returned later. 
// Use the vector method pop_back() to remove the last item from the heap structure. 
// Call the function downheap() to move the first non-sentinel item in the heap down the heap structure to its proper location. 
// Finally, return the item retrieved earlier to the calling function.
template <class T, class Pred>
T remove (std::vector<T>& heap_vector, Pred pred){
	
	std::swap (heap_vector[1],heap_vector[heap_vector.size()-1]);
	T temp= heap_vector.back();
	heap_vector.pop_back();
	unsigned int firstIndex=1;
	downheap(heap_vector,firstIndex,pred);
	return temp;
}


// This function moves an item at a given starting index (the second argument) up a heap structure (the first argument) 
// with the given order (the third argument) until it reaches its proper location. 
// The item should be compared (and swapped as necessary) with its parent in the heap until the given order has been satisfied. 
// Note that for an item at index k in the vector, the item's parent in the heap will be located at index k / 2.
// To make the code for upheap() function easier, it is easiest to create the heap vector with a starter element. 
// This sentinel element will always occupy the first slot of the vector (index 0); 
// it should not be considered to be part of the heap; and it should never be removed from the vector.

template <class T, class Pred>
void upheap (std::vector<T>& heap_vector, unsigned int childIndex, Pred pred){
	
	unsigned int parentIndex=childIndex/2;
	
	while ( parentIndex!=0 && pred (heap_vector[childIndex], heap_vector[parentIndex] ) ) {
		std::swap( heap_vector[parentIndex], heap_vector[childIndex] );
		childIndex=parentIndex;
		parentIndex=parentIndex/2;
	}
	
}

// This function is used to move an item at a given starting index (the second argument) down a heap structure (the first argument) 
// with the given order (the third argument) until it reaches its proper location. 
// The item should be compared (and swapped as necessary) with its appropriate child in the heap until the given order has been satisfied.
// Note that for an item at index k in the vector,
// the item's left child in the heap will be located at index 2 * k and its right child in the heap will be located at index 2 * k + 1.

template <class T, class Pred>
void downheap (std::vector<T>& heap_vector, unsigned int parentIndex, Pred pred) { 
	
	unsigned int leftChild= parentIndex*2;
	unsigned int totalItems= heap_vector.size();
	unsigned int largerChild=0;

	while (leftChild < totalItems) {

		largerChild=leftChild;
		int rightChild=leftChild+1;
		
		if ( leftChild<(totalItems-1) && pred (heap_vector[rightChild], heap_vector[leftChild]) ) {
			largerChild=rightChild;
		}

		if ( pred(heap_vector[largerChild], heap_vector[parentIndex]) ){
			std::swap ( heap_vector[largerChild], heap_vector[parentIndex] );
			parentIndex=largerChild;
			leftChild=largerChild*2;
		}
		else break;

		//leftChild++;
	}
}

#endif