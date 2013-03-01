#ifndef BASEBALLPLAYER_H
#define BASEBALLPLAYER_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

class BaseballPlayer{
	
	public:
		BaseballPlayer (std::string nm="",int w=0,int h=0);
		std::string get_name ()const;
		virtual void print_player()=0;
		virtual void load_player(std::ifstream&)=0;
		virtual ~BaseballPlayer(){}
	protected:
		std::string name;
		int height;
		int weight;
};

#endif
