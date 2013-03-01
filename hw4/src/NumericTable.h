#ifndef NUMERICTABLE_H
#define NUMERICTABLE_H

#include <iostream>
#include <map>
#include <string>

class NumericTable {

	typedef std::map <int, int> MapType; 
	
	public:
		NumericTable();
		void add(int);
		void print(const std::string &)const;
		int distinctItem_count()const;
		~NumericTable(){}
		
	private:
		MapType nMap;
		int generalItem_count;
};

#endif