#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <map>
#include <string>

class Table {

	typedef std::map <std::string, int> MapType; 
	
	public:
		Table();
		void add(const std::string &);
		void print(const std::string &)const;
		int distinctItem_count()const;
		~Table(){}
	
	private:
		MapType map;
		int generalItem_count;
};

#endif