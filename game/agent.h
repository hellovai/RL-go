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
	vector<Coor> priority;
	//difficulty of agent
	int level;
	double c;

	//type of agent
	int type;
	
	//types of moves
	Coor Random();
	Coor Heuristic();
	Coor UCTSearch ();
	Node* Simulate( );
	vector<TreeStruct> SimTree(Node* prev);
	void BackUp( vector<TreeStruct> preferred, int win );
	Coor RaveUCTSearch ( );
	Node* RaveSimulate( );
	vector<TreeStruct> RaveSimTree(Node* prev);
	void RaveBackUp( int T, vector<TreeStruct> preferred, int win );
	Coor RaveSelectMove(Node* );

	Coor SelectMove(Node* );
	vector<int> ConvertOneD();
	int ConvertOneD(Coor );
	void GetValidMoves();
	int Default();

	public:
		Agent( Game*, UCT*, double );
		void Change_game ( Game* curr_game ) { game = curr_game; };
		void setDebug( bool debg ) { debug = debg; };
		void setType( int ty ) { type = ty; };
		void setLevel( int lev ) { level = lev; };
		
		Coor Move( );
};

//=================================
// end guard
#endif
//=================================
