#ifndef PITCHER_CPP
#define PITCHER_CPP

#include <iomanip>
#include "Pitcher.h"

Pitcher::Pitcher(std::string nm,int w,int h,char t,float i,int e) : BaseballPlayer(nm,w,h) {
	throws=t;
	inningsPitched=i;
	earnedRuns=e;
	ERA= utility();
}


void Pitcher::print_player(){
	std::cout<<"Pitcher -"<<std::endl;
	std::cout<<"Name:  "<<name<<std::endl;
	std::cout<<"Height:  "<<height<<" inches"<<std::endl;
	std::cout<<"Weight:  "<<weight<<" pounds"<<std::endl;
	std::cout<<"Throws:  "<<throws<<std::endl;
	std::cout<<"EarnedRuns:  "<<earnedRuns<<std::endl;
	std::cout<<"Innings Pitched:  "<<std::fixed<<std::setprecision(3)<<inningsPitched<<std::endl;
	std::cout<<"ERA:  "<<std::fixed<<std::setprecision(2)<<ERA<<std::endl<<std::endl;
}



void Pitcher::load_player(std::ifstream& input){
	
	input>>name>>height>>weight>>throws>>earnedRuns>>inningsPitched;
	ERA=utility();
	
	/******** another method*************
	=====================================
	
	std::string temp;
	std::getline (input,temp);
		
	int posNil=0;
	int nextNil=0;
	for (int i=0;i<temp.size();i++){
		char check=temp.at(i);
		if (isspace(check)){
			posNil=i;
			break;
		}
	}
	name=temp.substr(0,posNil);
		
	for (int i=posNil+1;i<temp.size();i++){
		char check=temp.at(i);
		if (isspace(check)){
			nextNil=i;
			break;
		}
	}
	height= atoi((temp.substr(posNil+1, nextNil-1)).c_str());
	
	for (int i=nextNil+1;i<temp.size();i++){
		char check=temp.at(i);
		if (isspace(check)){
			posNil=i;
			break;
		}
	}
	weight= atoi((temp.substr(nextNil+1,posNil-1)).c_str());
	
	posNil++;
	throws=temp.at(posNil);
	posNil++;
	
	for (int i=posNil+1;i<temp.size();i++){
		char check=temp.at(i);
		if (isspace(check)){
			nextNil=i;
			break;
		}
	}
	earnedRuns= atoi((temp.substr(posNil+1,nextNil-1)).c_str());
	inningsPitched= atof((temp.substr(nextNil+1)).c_str());
	*/
	
}


float Pitcher::utility(){
	if (inningsPitched==0.0)
		return 999.99;
	else return earnedRuns/inningsPitched*9.0;
}

#endif 