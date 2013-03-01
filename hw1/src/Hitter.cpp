#ifndef HITTER_CPP
#define HITTER_CPP

#include <iomanip>
#include "Hitter.h"

Hitter::Hitter(std::string nm,int w,int h,char b,int atB,int ht) : BaseballPlayer(nm,w,h) {
	bats=b;
	atBats=atB;
	hits=ht;
	batAvg=utility();
}


void Hitter::print_player(){
	
	std::cout<<"Hitter -"<<std::endl;
	std::cout<<"Name:  "<<name<<std::endl;
	std::cout<<"Height:  "<<height<<" inches"<<std::endl;
	std::cout<<"Weight:  "<<weight<<" pounds"<<std::endl;
	std::cout<<"Bats:  "<<bats<<std::endl;
	std::cout<<"Hits:  "<<hits<<std::endl;
	std::cout<<"At Bats:  "<<atBats<<std::endl;
	std::cout<<"Batting Average:  "<<std::fixed<<std::setprecision(3)<<batAvg<<std::endl<<std::endl;

}


void Hitter::load_player(std::ifstream& input){
		
	input>>name>>height>>weight>>bats>>hits>>atBats;
	batAvg=utility();
	
	/***** a different method************
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
	height=atoi((temp.substr(posNil+1, nextNil-1)).c_str());
	
	for (int i=nextNil+1;i<temp.size();i++){
		char check=temp.at(i);
		if (isspace(check)){
			posNil=i;
			break;
		}
	}
	weight=atoi((temp.substr(nextNil+1,posNil-1)).c_str());
	
	posNil++;
	bats=temp.at(posNil);
	posNil++;
	
	for (int i=posNil+1;i<temp.size();i++){
		char check=temp.at(i);
		if (isspace(check)){
			nextNil=i;
			break;
		}
	}
	hits= atoi((temp.substr(posNil+1,nextNil-1)).c_str());
	atBats= atoi((temp.substr(nextNil+1)).c_str());
	*/

}


float Hitter::utility(){
	if (atBats==0)
		return 0;
		
	else
		return hits/(double)atBats;
}

#endif