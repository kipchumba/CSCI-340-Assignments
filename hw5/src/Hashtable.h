#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>


template <typename T, typename HashFunction>
class HashTable{
	
	public:
		HashTable(int);
		void clear();
		int getsize();
		int bucketsUsed();
		int maxLength();
		bool isEmpty();
		bool insert(T);
		bool find(T&);
		
	private:
		std::vector<std::list<T> > buckets;
		int bucketsNum;
		int elementsNum;
		HashFunction hash;
};


/*
 * Name         : HashTable
 * Synopsis     : HashTable (int n) *
 * Arguments    : int  n : 
 * Description  : the only constructor, creates a hashtable with the given number of empty lists (buckets)
 * Returns      : 
 */
template <typename T, typename HashFunction>
HashTable<T,HashFunction>::HashTable (int n) : buckets(n),bucketsNum(n),elementsNum(0){}


/*
 * Name         : clear
 * Synopsis     : clear () *
 * Description  : clears the vector of buckets, resetting size to nil
 * Returns      : void
 */
template <typename T, typename HashFunction>
void HashTable<T,HashFunction>::clear (){
	buckets.clear();
	elementsNum=0;
	bucketsNum=0;
	return;
}


/*
 * Name         : getsize
 * Synopsis     : getsize() *
 * Description  : returns the total number of items being held in the buckets
 * Returns      : elementsNum
 */
template <typename T, typename HashFunction>
int HashTable<T,HashFunction>::getsize(){
	return elementsNum;
}


/*
 * Name         : bucketsUsed
 * Synopsis     : bucketsUsed() *
 * Description  : returns the number of non-empty buckets in the vector
 * Returns      : bucketsNum
 */
template <typename T, typename HashFunction>
int HashTable<T,HashFunction>::bucketsUsed(){
	int bucketsInUse=0;
	if (bucketsNum==0) 
		return 0;
	for (int x=0;x<bucketsNum;x++){
		if (buckets[x].empty()){};
		bucketsInUse++;
	}
	return bucketsInUse;
}

template <typename T, typename HashFunction>
int HashTable<T,HashFunction>::maxLength () {
	int max=0;
	if (buckets.empty())
		return max;
	for (int x=0;x<bucketsNum;x++){
		if ((buckets[x].size())>max)
			max=buckets[x].size();
	}
	return max;
}

template <typename T, typename HashFunction>
bool HashTable<T,HashFunction>::isEmpty(){
	return (buckets.empty());
}

template <typename T, typename HashFunction>
bool HashTable<T,HashFunction>::insert(T data){
	int x=bucketsNum;
	int index=(hash(data))%x;
	if (!find(data)) {
		buckets[index].push_front(data);
		elementsNum++;
		return true;
	}
	else 
		return false;
}

template <typename T, typename HashFunction>
bool HashTable<T,HashFunction>::find (T& data){
	int x=bucketsNum;
	int index=(hash(data))%x;
	
	/* ============= using iterator ===================*/
	typename std::list<T>::iterator iter;
	for (iter=buckets[index].begin();
			iter!=buckets[index].end();iter++) {
				if (*iter==data)
					return true;
	}
	return false;
	
	/* ==============using std::find=========================*/
	/*typename std::list<T>::iterator position= std::find(buckets[index].begin(), 
											buckets[index].end(), data);
	if (position==buckets[index].end())
		return false;
	else 
		return true;
	*/
}
#endif