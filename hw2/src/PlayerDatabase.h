#ifndef PLAYERDATABASE_H
#define PLAYERDATABASE_H

#include <vector>
#include "BaseballPlayer.h"
#include "Hitter.h"
#include "Pitcher.h"

class PlayerDatabase {
	
	public:
		PlayerDatabase();
		PlayerDatabase(PlayerDatabase const&);
		PlayerDatabase& operator= (PlayerDatabase const&);
		~PlayerDatabase();
		void print_team(std::ofstream&) const;
		void load_team(std::ifstream&);
		void create_good_team();
		void create_small_team();
		int get_team_count() const;
			
	private:
		std::vector<BaseballPlayer*> team;
};

#endif