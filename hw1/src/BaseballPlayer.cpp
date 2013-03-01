#ifndef BASEBALLPLAYER_CPP
#define BASEBALLPLAYER_CPP

#include "BaseballPlayer.h"

BaseballPlayer::BaseballPlayer (std::string nm,int w,int h) {
	name=nm;
	weight=w;
	height=h;
}


std::string BaseballPlayer::get_name ()const{
	return name;
}

#endif