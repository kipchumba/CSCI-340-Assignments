#ifndef CREATE_NAMES_CPP
#define CREATE_NAMES_CPP

#include "create_names.h"

void create_names(int argc, char* argv[], std::string& iFileName, std::string& oFileNameAll, 
					std::string& oFileNameGood, std::string& oFileNameSmall, std::string& oFileNameRepeat){
	iFileName=argv[1];	
	int iFileSize= iFileName.size();
	oFileNameAll= iFileName.substr(0,iFileSize-4)+"_output_all.txt";
	oFileNameGood= iFileName.substr(0,iFileSize-4)+"_output_good.txt";
	oFileNameSmall= iFileName.substr(0,iFileSize-4)+"_output_small.txt";
	oFileNameRepeat= iFileName.substr(0,iFileSize-4)+"_output_repeat.txt";			
}

#endif