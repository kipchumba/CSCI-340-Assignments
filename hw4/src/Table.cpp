
#include <iomanip>
#include "Table.h"

Table::Table(): map(){
	generalItem_count=0;
}

void Table::add(const std::string &str){
	map[str]++;
	generalItem_count++;
	return;
}

void Table::print(const std::string &str) const{
	std::cout<<str<<std::endl<<std::endl;
	std::cout<<"Number of distinct entries = "<<std::setw(3)<<std::right<<distinctItem_count()<<std::endl;
	std::cout<<"Number of entries          = "<<std::setw(3)<<std::right<<generalItem_count<<std::endl;
	std::cout<<std::endl;
	
	MapType::const_iterator begin=map.begin();
	MapType::const_iterator end=map.end();
	
	while (begin!=end){
		int counter=0;
		while ((counter<5)&&(begin!=end)){
			std::cout<<std::setw(13)<<std::left<<begin->first<<std::setw(3)<<std::right<<begin->second<<"    ";
			begin++;
			counter++;
		}
		std::cout<<"\n";
	}
	
	
}

int Table::distinctItem_count()const{
	return map.size();
}
