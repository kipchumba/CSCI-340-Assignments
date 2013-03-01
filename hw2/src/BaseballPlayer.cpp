#ifndef BASEBALLPLAYER_CPP
#define BASEBALLPLAYER_CPP

#include "BaseballPlayer.h"

BaseballPlayer::BaseballPlayer (std::string s,int w,int h) {
	name=s;
	weight=w;
	height=h;
}


std::string BaseballPlayer::get_name ()const{
	return name;
}

#endif