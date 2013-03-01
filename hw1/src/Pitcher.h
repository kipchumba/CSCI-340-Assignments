#ifndef PITCHER_H
#define PITCHER_H

#include "BaseballPlayer.h"

const char THROWS_UNINITIALIZED='U';
class PlayerDatabase;

class Pitcher: public BaseballPlayer {
	
	public:
		Pitcher(std::string nm="",int w=0,int h=0,char t=THROWS_UNINITIALIZED ,float i=0.0,int e=0);
		virtual void print_player();
		virtual void load_player(std::ifstream&);
		virtual ~Pitcher(){}
		friend class PlayerDatabase;
		
	private:
		char throws;
		float inningsPitched;
		int earnedRuns;
		float ERA;
		float utility();
};

#endif