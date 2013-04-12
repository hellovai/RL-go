//=================================
// include guard
#ifndef __AGENT_H_INCLUDED__
#define __AGENT_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Agent {
	Game* game;
	//UCT* movelist;
	bool debug;
	vector<Coor> moveData;
	
	//type of agent
	int type;
	
	//types of moves
	int Random();
	int UCTVanilla();

	public:
		Agent( Game* curr_game );
		void Change_game ( Game* curr_game ) { game = curr_game; };
		void setDebug( bool debg ) { debug = debg; };
		void setType( int ty ) { type = ty; };
		
		Coor Move( );
};

//=================================
// end guard
#endif
//=================================
