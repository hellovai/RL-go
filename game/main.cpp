#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;

int main (int argc, char* argv[]) {
	srand (time(NULL));
	
	int boardsize = 9;
	bool c1 = false;
	bool c2 = false;
	bool debug = false;
	bool dolog = false;

	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if(temp.compare("-big") == 0) {
			boardsize = 19;
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
		} else if (temp.compare("-log") == 0) {
			dolog = true;
		} else if (temp.compare("-debug") == 0) {
			debug = true;
		}else
			usage_err(temp);
	}

	// print starting config
	cout<<"Configuration: "<<endl;
	cout<<"\tBoardsize:\t"<<boardsize<<endl;
	cout<<"\tPlayer 1:\t"<<(c1 ? "Agent" : "Human")<<endl;
	cout<<"\tPlayer 2:\t"<<(c2 ? "Agent" : "Human")<<endl;
	
	Game* game = new Game(boardsize);
	Agent* p1 = new Agent(game);
	p1->setType(1);
	
	Agent* p2 = new Agent(game);
	
	cout<<"Starting Game...\n";
	//create game
	while(!game->Status()) {
		if(debug || !(game->Turn() == -1 ? c1 : c2 )) game->Print();
		
		//play game
		Coor move(-1,-1);
		
		// alternate moves once agent is ready
		do {
			if(game->Turn() == -1)
				if(c1) move = p1->Move();
				else move = getHuman();
			else
				if(c2) move = p2->Move();
				else move = getHuman();
		} while(!game->ValidMove(move));

		game->Move();
	}

	//display result
	game->Score();
	
	return 0;
}

void usage_err(string var) {
	cout<<"Improper usage of '"<<var<<"'"<<endl;
	cout<<"Usage: ./go "<<endl;
	exit(0);
}

Coor getHuman() {
	Coor move(-1,-1);
	cin>>move.x>>move.y;
	cout<<"Move: "<<move.x<<" "<<move.y<<endl;
	return move;
}
