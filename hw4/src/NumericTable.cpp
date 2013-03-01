#include <iomanip> 	
#include "NumericTable.h"

NumericTable::NumericTable() : nMap(){
	generalItem_count=0;
}

void NumericTable::add(int n){
	nMap[n]++;
	generalItem_count++;
	return;
}

void NumericTable::print(const std::string & str) const{
	std::cout<<str<<std::endl<<std::endl;
	std::cout<<"Number of distinct entries = "<<std::setw(3)<<std::right<<distinctItem_count()<<std::endl;
	std::cout<<"Number of entries          = "<<std::setw(3)<<std::right<<generalItem_count<<std::endl;
	std::cout<<std::endl;

	
	MapType::const_iterator begin=nMap.begin();
	MapType::const_iterator end=nMap.end();
	
	while (begin!=end){
		int counter=0;
		while ((counter<5)&&(begin!=end)){
			std::cout<<std::setw(3)<<std::right<<begin->first<<"  "<<std::setw(3)<<std::right<<begin->second<<"   ";
			begin++;
			counter++;
		}
		std::cout<<"\n";
	}
	
}

int NumericTable::distinctItem_count()const{
	return nMap.size();

}
