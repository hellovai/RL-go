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
	UCT* UCTtree;
	bool debug;
	vector<Coor> moveData;
	
	//difficulty of agent
	int level;

	//type of agent
	int type;
	
	//types of moves
	Coor Random();
	Coor UCTSearch ();
	Node* Simulate( );
	vector<TreeStruct> SimTree(Node* prev);
	int Default();
	void BackUp( vector<TreeStruct> preferred, int win );
	Coor SelectMove(Node* );
	vector<int> ConvertOneD();
	int ConvertOneD(Coor );
	void GetValidMoves();

	public:
		Agent( Game*, UCT* );
		void Change_game ( Game* curr_game ) { game = curr_game; };
		void setDebug( bool debg ) { debug = debg; };
		void setType( int ty ) { type = ty; };
		
		Coor Move( );
};

//=================================
// end guard
#endif
//=================================
