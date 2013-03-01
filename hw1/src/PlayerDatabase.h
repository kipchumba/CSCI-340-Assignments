#ifndef PLAYERDATABASE_H
#define PLAYERDATABASE_H

#include "BaseballPlayer.h"
#include "Hitter.h"
#include "Pitcher.h"

class PlayerDatabase {
	
	public:
		PlayerDatabase();
		PlayerDatabase(const PlayerDatabase&);
		PlayerDatabase& operator= (const PlayerDatabase&);
		~PlayerDatabase();
		void print_team() const;
		void load_team(std::ifstream&);
		
	
	private:
		int team_count;
		int MAX_SIZE;
		BaseballPlayer** players;
		void resize();
		bool isMaxSize();
		void destroy();

};

#endif