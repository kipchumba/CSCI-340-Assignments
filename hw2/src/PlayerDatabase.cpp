#ifndef PLAYERDATABASE_CPP
#define PLAYERDATABASE_CPP

#include <iomanip>
//#include "cppMemDbg.h"
#include "PlayerDatabase.h"

const char HITTER='H';
const char PITCHER='P';
const int REDUCE_BY=4;

PlayerDatabase::PlayerDatabase(){
}

PlayerDatabase::PlayerDatabase(PlayerDatabase const& right){
	std::vector<BaseballPlayer*>::iterator begin, end;
	begin=right.team.begin();
	end=right.team.end();
	
	while (begin!=end){
		Pitcher* pPlayer= dynamic_cast<Pitcher*>(*begin);
		if (pPlayer){
			Pitcher* pitcher= new Pitcher(*pPlayer);
			team.push_back(dynamic_cast<BaseballPlayer*>(pitcher));
		}
		
		else{
			Hitter* hPlayer= dynamic_cast<Hitter*>(*begin);
			Hitter* hitter= new Hitter(*hPlayer);
			team.push_back(dynamic_cast<BaseballPlayer*>(hitter));
		}
		
		begin++;
	}
	
}

PlayerDatabase& PlayerDatabase::operator= (PlayerDatabase const& right){
	if (team==right.team)
		return *this;
	
	else {
		std::vector<BaseballPlayer*>::iterator begin, end;
		begin=right.team.begin();
		end=right.team.end();
		
		while (begin!=end){
				
			Pitcher* pPlayer= dynamic_cast<Pitcher*>(*begin);
			if (pPlayer){
				Pitcher* pitcher= new Pitcher(*pPlayer);
				BaseballPlayer* bplayer= dynamic_cast<BaseballPlayer*>(pitcher);
				team.push_back(bplayer);
			}
			
			else{
				Hitter* hPlayer= dynamic_cast<Hitter*>(*begin);
				Hitter* hitter= new Hitter(*hPlayer);
				BaseballPlayer* bplayer= dynamic_cast<BaseballPlayer*>(hitter);
				team.push_back(bplayer);
			}
			begin++;
		}
	}
	return *this;
}

PlayerDatabase::~PlayerDatabase(){
	std::vector<BaseballPlayer*>::iterator iter;
	for (iter=team.begin();iter!=team.end();iter++){
		if (*iter)
			delete *iter;
		*iter=nullptr;
	}
	team.clear();
}

void PlayerDatabase::print_team(std::ofstream& outputFile) const{
	int totalHits=0, totalAtBats=0, totalEarnedRuns=0;
	float totalInningsPitched=0.0;
	
	std::vector<BaseballPlayer*>::iterator begin, end;
	begin=team.begin();
	end=team.end();
	int member=1;
	
	while (begin!=end){
		std::cout<<"Member "<<member<<std::endl;
		(*begin)->print_player(outputFile);
		
		Pitcher* pPlayer= dynamic_cast<Pitcher*>(*begin);
		if (pPlayer){
			totalEarnedRuns+=pPlayer->earnedRuns;
			totalInningsPitched+=pPlayer->inningsPitched;
			begin++;
			member++;
		}
		
		else{
			Hitter* hPlayer= dynamic_cast<Hitter*>(*begin);
			totalHits+=hPlayer->hits;
			totalAtBats+=hPlayer->atBats;
			begin++;
			member++;
		}
		
	}
	
	if(totalAtBats==0||totalInningsPitched==0.0){
		
		if(totalAtBats==0&&totalInningsPitched==0.0){
			std::cout<<"Team Batting Average: "<<"n/a"<<std::endl;
			std::cout<<"Team ERA: "<<"n/a"<<std::endl;
		}
		else if (totalAtBats==0){
			std::cout<<"Team Batting Average: "<<"n/a"<<std::endl;
			std::cout<<"Team ERA: "<<(totalEarnedRuns/totalInningsPitched*9)<<std::endl;
		}
		else {
			std::cout<<"Team Batting Average: "<<std::fixed<<std::setprecision(3)<<totalHits/(double)totalAtBats<<std::endl;
			std::cout<<"Team ERA: "<<"n/a"<<std::endl;
		}
	}
	
	else{
		std::cout<<"Team Batting Average: "<<std::fixed<<std::setprecision(3)<<totalHits/(double)totalAtBats<<std::endl;
		std::cout<<"Team ERA: "<<(totalEarnedRuns/totalInningsPitched*9)<<std::endl;
	}
}

void PlayerDatabase::load_team(std::ifstream& input){
	int counter=1;
	while (!input.eof()){
		char playerType;
		input.get(playerType);
		
		if (playerType==HITTER){
			Hitter* hitter= new Hitter;
			hitter->load_player(input);
			std::cout<<"Loading member "<<counter<<std::endl;
			team.push_back(dynamic_cast<BaseballPlayer*>(hitter));
			counter++;
		}
		
		else if (playerType==PITCHER){
			Pitcher* pitcher= new Pitcher;
			pitcher->load_player(input);
			std::cout<<"Loading member "<<counter<<std::endl;
			team.push_back(dynamic_cast<BaseballPlayer*>(pitcher));
			counter++;
		}
		
	}
}

void PlayerDatabase::create_good_team(){
	
	std::vector<BaseballPlayer*> goodTeam;
	
	std::vector<BaseballPlayer*>::iterator begin, end;
	begin=team.begin();
	end=team.end();
	
	while (begin!=end){
				
		Pitcher* pPlayer= dynamic_cast<Pitcher*>(*begin);
		if (pPlayer){
			if(pPlayer->goodPitcher()){
				
				goodTeam.push_back(dynamic_cast<BaseballPlayer*>(pPlayer));
			}
			else {
				if (*begin)
					delete *begin;
				*begin=nullptr;
			}
			begin++;
		}
		
		else{
			Hitter* hPlayer= dynamic_cast<Hitter*>(*begin);
			if(hPlayer->goodHitter()){
				goodTeam.push_back(dynamic_cast<BaseballPlayer*>(hPlayer));
			}
			else {
				if (*begin)
					delete *begin;
				*begin=nullptr;
			}
			begin++;
		}
	}
	team.clear();
	team=goodTeam;
}

void PlayerDatabase::create_small_team(){
	if(get_team_count()>=REDUCE_BY){
		std::vector<BaseballPlayer*>::iterator first, fifth;
		first= team.begin();
		fifth=first+REDUCE_BY;
		
		while (first!=fifth){
			if (*first)
				delete *first;
			*first=nullptr;
			first++;
		}
		team.erase(team.begin(),fifth);
	}
	
	else {
		std::vector<BaseballPlayer*>::iterator first,last;
		first= team.begin();
		last=team.end();
		while(first!=last){
			if (*first)
				delete *first;
			*first=nullptr;
			first++;
		}
		team.clear();
	}
}

int PlayerDatabase::get_team_count() const{
	return team.size();
}

#endif
