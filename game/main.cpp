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
#include "node.h"
#include "uct.h"
#include "agent.h"

using namespace std;

int tboardsize;

int main (int argc, char* argv[]) {
	srand (time(NULL));
	
	int boardsize = 9;
	bool c1 = false;
	bool c2 = false;
	bool debug = false;
	bool dolog = false;
	bool pause = false;

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
		} else if (temp.compare("-p") == 0) {
			pause = true;
		} else
			usage_err(temp);
	}

	// print starting config
	cout<<"Configuration: "<<endl;
	cout<<"\tBoardsize:\t"<<boardsize<<endl;
	cout<<"\tPlayer 1:\t"<<(c1 ? "Agent" : "Human")<<endl;
	cout<<"\tPlayer 2:\t"<<(c2 ? "Agent" : "Human")<<endl;
	tboardsize = boardsize;
	Game* game = new Game(boardsize);
	UCT* gametree = new UCT(boardsize, debug);
	Agent* p1 = new Agent(game, gametree);
	Agent* p2 = new Agent(game, gametree);
	game->setDebug(false);
	p1->setDebug(debug);
	p2->setDebug(debug);
	
	p1->setType(1);
	p2->setType(1);
	int counter = 0;
	
	cout<<"Starting Game...\n";
	//create game
	while(!game->Status()) {
		if(debug || !(game->Turn() == -1 ? c1 : c2 ) || pause) game->Print();
		//if(debug || pause) cin.ignore();
		//play game
		Coor move(-1,-1);
		
		// alternate moves once agent is ready
		int checker = 0;
		do {
			if(checker == 1) {
				cout<<"Returned invalid move "<<game->Turn()<<endl;
				for(int i=0; i<(int) game->History().size(); i++)
					cout<<game->History()[i].x<<","<<game->History()[i].y<<endl;
				game->printPrev();
				game->Print();
				exit(0);
			}
			if(game->Turn() == -1)
				if(c1) move = p1->Move();
				else move = getHuman();
			else
				if(c2) move = p2->Move();
				else move = getHuman();
			if(debug) cout<<"While Loop: "<<move.x<<","<<move.y<<endl;
			checker ++;
		} while(!game->ValidMove(move));

		game->Move(move);
		cout<<"Move "<<++counter<<endl;
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

Coor mapRotate(Coor data, int rotater) {
	//cout<<"begginning mapRotate"<<endl;
		int x = data.x, y = data.y;
		if(x == -1 || y == -1)
			return data;
		switch (rotater) {
			case 1:
				data = Coor( x, tboardsize-1-y ); break;
			case 2:
				data = Coor( tboardsize-1-x, y ); break;
			case 3:
				data = Coor( y, x ); break;
			case 4:
				data = Coor( tboardsize-1-y, tboardsize-1-x ); break;
			case 5:
				data = Coor( tboardsize-1-y, x ); break;
			case 6:
				data = Coor( tboardsize-1-x, tboardsize-1-y ); break;
			case 7:
				data = Coor( y, tboardsize-1-x ); break;
			default:
				data = Coor( x, y); break;
		}
		return data;
}