#ifndef HITTER_H
#define HITTER_H

#include "BaseballPlayer.h"
const char BATS_UNINITIALIZED='U';
class PlayerDatabase;

class Hitter: public BaseballPlayer {
	
	public:
		Hitter(std::string="",int w=0,int h=0,char b=BATS_UNINITIALIZED,int atB=0,int ht=0);
		virtual void print_player(std::ofstream&);
		virtual void load_player(std::ifstream&);
		bool goodHitter();
		virtual ~Hitter(){}
		friend class PlayerDatabase;
	private:
		char bats;
		int atBats;
		int hits;
		float batAvg;
		float utility();
};

#endif