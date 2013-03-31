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
// #include "agent.h"

using namespace std;

int main (int argc, char* argv[]) {
	bool c1 = false;
	bool c2 = false;
	bool dolog = false;

	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if(temp.compare("-b") == 0) {
			if(++i >= argc) usage_err(temp);
			BOARDSIZE = atoi(argv[i]);
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
		} else if (temp.compare("-log") == 0) {
			dolog = true;
		} else
			usage_err(temp);
	}

	BOARDSIZE = max(9, BOARDSIZE);
	BOARDSIZE = min(BOARDSIZE, 19);

	Game game(BOARDSIZE);
	game.ValidMove();

	//create game
	while(!game.Status()) {
		game.Print();
		
		//play game
		Coor move;
		
		// alternate moves once agent is ready
		// if(game->turn() == -1)
		// 	if(c1) move = agent1->move();
		// 	else move = getHuman();
		// else
		// 	if(c2) move = agent2->move();
		// 	else move = getHuman();
		
		move = getHuman();
		while(!game.Move(move)) {
			cout<<"Sorry, ("<<move.x<<" , "<<move.y<<") is invalid!\n";
			move = getHuman();
		}
	}

	//display result
	return 0;
}

void usage_err(string var) {
	cout<<"Usage: ./go "<<endl;
	exit(0);
}

Move getHuman() {
	Move move;
	cout<<"Enter Move: ";
	cin>>move.x>>move.y;
	return move;
}