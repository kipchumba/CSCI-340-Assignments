#ifndef PLAYERDATABASE_CPP
#define PLAYERDATABASE_CPP

#include <iomanip>
#include <debug_new.h>
#include "PlayerDatabase.h"

const char HITTER='H';
const char PITCHER='P';
const int DEFAULT_SIZE=50;

PlayerDatabase::PlayerDatabase(){
 team_count=0;
}

PlayerDatabase::PlayerDatabase(const PlayerDatabase& right){
    team_count=right.team_count;
    players= new BaseballPlayer* [team_count];
    for (int i=0;i<team_count;i++){
        Pitcher* pPlayer= dynamic_cast<Pitcher*>(right.players[i]);
        if (pPlayer){
            Pitcher* pitcher= new Pitcher(*pPlayer);
            players[i]=dynamic_cast<BaseballPlayer*>(pitcher);
        }
        else{
            Hitter* hPlayer= dynamic_cast<Hitter*>(right.players[i]);
            Hitter* hitter= new Hitter(*hPlayer);
            players[i]=dynamic_cast<BaseballPlayer*>(hitter);
        }
    }
}


PlayerDatabase& PlayerDatabase::operator= (const PlayerDatabase& right){
    if (team_count==right.team_count){
        int checker=0;
        for (int i=0;i<team_count;i++){
            if(this->players[i]==right.players[i])
                checker++;
        }
        if(checker==team_count)
            return *this;
    }

    else {
        if (team_count>0)
            destroy();
        team_count=right.team_count;
        players= new BaseballPlayer* [team_count];
        for (int i=0;i<team_count;i++){
            Pitcher* pPlayer= dynamic_cast<Pitcher*>(right.players[i]);
            if (pPlayer){
                Pitcher* pitcher= new Pitcher(*pPlayer);
                this->players[i]=dynamic_cast<BaseballPlayer*>(pitcher);
            }

            else{
                Hitter* hPlayer= dynamic_cast<Hitter*>(right.players[i]);
                Hitter* hitter= new Hitter(*hPlayer);
                this->players[i]=dynamic_cast<BaseballPlayer*>(hitter);
            }
        }
    }
    return *this;
}


PlayerDatabase::~PlayerDatabase(){
    destroy();
	delete [] players;
    team_count=0;
}


void PlayerDatabase::print_team() const{
    int totalHits=0, totalAtBats=0, totalEarnedRuns=0;
    float totalInningsPitched=0.0;
	std::cout<<"Team size: "<<team_count<<std::endl;
    for (int i=0;i<team_count;i++){
        std::cout<<"Member "<<i+1<<std::endl;
        players[i]->print_player();

        Pitcher* pPlayer= dynamic_cast<Pitcher*>(players[i]);
        if (pPlayer){
            totalEarnedRuns+=pPlayer->earnedRuns;
            totalInningsPitched+=pPlayer->inningsPitched;
        }

        else{
            Hitter* hPlayer= dynamic_cast<Hitter*>(players[i]);
            totalHits+=hPlayer->hits;
            totalAtBats+=hPlayer->atBats;
        }
    }
    std::cout<<"Team Batting Average: "<<std::fixed<<std::setprecision(3)<<totalHits/(double)totalAtBats<<std::endl;
    std::cout<<"Team ERA: "<<(totalEarnedRuns/totalInningsPitched*9)<<std::endl;

}


void PlayerDatabase::load_team(std::ifstream& input){
    int counter=0;
	players= new BaseballPlayer* [DEFAULT_SIZE];
    MAX_SIZE=DEFAULT_SIZE;

    while (!input.eof()){
        char playerType;
        input.get(playerType);

        if (playerType==HITTER){
            Hitter* hitter= new Hitter();
            hitter->load_player(input);
            std::cout<<"Loading member "<<counter+1<<std::endl;
            if(isMaxSize())
                resize();
            players[counter]=dynamic_cast<BaseballPlayer*>(hitter);
            counter++;
			team_count++;
            }

        else if (playerType==PITCHER){
            Pitcher* pitcher= new Pitcher();
            pitcher->load_player(input);
            std::cout<<"Loading member "<<counter+1<<std::endl;
            if(isMaxSize())
                resize();
            players[counter]=dynamic_cast<BaseballPlayer*>(pitcher);
            counter++;
			team_count++;
        }
    }
}

void PlayerDatabase::resize(){
    MAX_SIZE*=2;
    BaseballPlayer** data= new BaseballPlayer* [MAX_SIZE];
    for (int i=0;i<team_count;i++){
        data[i]=players[i];
    }

    delete [] players;
    players=data;
	//delete[] data;    // deleted in the destructor
}

bool PlayerDatabase::isMaxSize(){
    return (team_count==MAX_SIZE);
}

void PlayerDatabase::destroy(){
    for (int i=0;i<team_count;i++){
        delete players[i];
        players[i]=NULL;
    }
}

#endif
