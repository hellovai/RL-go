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
	bool selfplay = true;
	bool score = false;
	int gameCounter = 1;
	int p1level = 1, p2level = 1;
	int p1type = 0, p2type = 0;
	double p1c = 1, p2c = 1;
	string treeout = "", tree2out = "", loadone = "", loadtwo = ""; 

	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if(temp.compare("-board") == 0) {
			if(++i < argc)
				boardsize = atoi(argv[i]);
			else
				usage_err(temp);
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
			bool check = true;
			while(check && ++i < argc) {
				temp = argv[i];
				if ( temp.compare("-level") == 0 ) {
					if(++i<argc)
						p1level = atoi(argv[i]);
					else
						usage_err(temp);
				} else if ( temp.compare("-type") == 0 ) {
					if(++i<argc)
						p1type = atoi(argv[i]);
					else
						usage_err(temp);
				} else if ( temp.compare("-cvar") == 0 ) {
					if(++i<argc)
						p1c = atof(argv[i]);
					else
						usage_err(temp);
				} else if ( temp.compare("-dump") == 0 ) {
					if(++i<argc)
						treeout = argv[i];
					else
						usage_err(temp);
				} else if ( temp.compare("-load") == 0 ) {
					if(++i<argc)
						loadone = argv[i];
					else
						usage_err(temp);
				} else {
					--i;
					check = false;
				}
			}
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
			bool check = true;
			while(check && ++i < argc) {
				temp = argv[i];
				if ( temp.compare("-level") == 0 ) {
					if(++i<argc)
						p2level = atoi(argv[i]);
					else
						usage_err(temp);
				} else if ( temp.compare("-type") == 0 ) {
					if(++i<argc)
						p2type = atoi(argv[i]);
					else
						usage_err(temp);
				} else if ( temp.compare("-cvar") == 0 ) {
					if(++i<argc)
						p2c = atof(argv[i]);
					else
						usage_err(temp);
				} else if ( temp.compare("-dump") == 0 ) {
					if(++i<argc)
						tree2out = argv[i];
					else
						usage_err(temp);
				} else if ( temp.compare("-load") == 0 ) {
					if(++i<argc)
						loadtwo = argv[i];
					else
						usage_err(temp);
				} else {
					--i;
					check = false;
				}
			}
		} else if (temp.compare("-log") == 0) {
			dolog = true;
		} else if (temp.compare("-debug") == 0) {
			debug = true;
		} else if (temp.compare("-p") == 0) {
			pause = true;
		} else if (temp.compare("-g") == 0) {
			if(++i<argc)
				gameCounter = atoi(argv[i]);
			else
				usage_err(temp);
		} else if (temp.compare("-selfoff") == 0) {
			selfplay = false;
		} else if (temp.compare("-score") == 0 ) {
			score = true;
		} else if (temp.compare("-level") == 0 ) {
			usage_err(temp);
		} else if (temp.compare("-type") == 0 ) {
			usage_err(temp);
		} else if (temp.compare("-h") == 0 ) {
			usage_err("");
		} else
			usage_err(temp);
	}
	//if not same type use different tree
	if(p1type != p2type) selfplay = false;

	// print starting config
	cout<<"Configuration: "<<endl;
	cout<<"\tBoardsize:\t"<<boardsize<<endl<<endl;
	cout<<"\tPlayer 1:\t"<<(c1 ? "Agent" : "Human")<<endl;
	if(c1) {		
		cout<<"\tType:\t\t";
		switch(p1type) {
			case 1:
				cout<<"UCT-Random";
				break;
			case 10:
				cout<<"UCT-Random";
				break;
			case 13:
				cout<<"UCT-Heuristic";
				break;
			case 2:
				cout<<"UCT-Rave";
				break;
			case 20:
				cout<<"UCT-Rave-Random";
				break;
			case 23:
				cout<<"UCT-Rave-Heuristic";
				break;
			case 3:
				cout<<"Heuristic";
				break;
			case 0:
			default:
				cout<<"Random";
		}
		cout<<endl;
		if(p1type == 1 || p1type == 2) cout<<"\tLevel:\t\t"<<p1level<<endl;
	}
	cout<<"\n\tPlayer 2:\t"<<(c2 ? "Agent" : "Human")<<endl;
	if(c2) {
		cout<<"\tType:\t\t";
		switch(p2type) {
			case 1:
				cout<<"UCT-Random";
				break;
			case 10:
				cout<<"UCT-Random";
				break;
			case 13:
				cout<<"UCT-Heuristic";
				break;
			case 2:
				cout<<"UCT-Rave";
				break;
			case 20:
				cout<<"UCT-Rave-Random";
				break;
			case 23:
				cout<<"UCT-Rave-Heuristic";
				break;
			case 3:
				cout<<"Heuristic";
				break;
			case 0:
			default:
				cout<<"Random";
		}
		cout<<endl;
		if(p2type == 1 || p2type == 2) cout<<"\tLevel:\t\t"<<p2level<<endl;
	}
	if(c1 && c2)
		cout<<"\n\tSelfplay:\t"<<(selfplay ? "Enabled" : "Disabled")<<endl;
	cout<<endl;
	if( (tree2out.length() != 0 || treeout.length() != 0) && selfplay )
		cout<<"\n\tOutput:\t"<<treeout<<endl;
	else if ((tree2out.length() != 0) && !selfplay) 
		cout<<"\n\tSecond Tree:\t"<<tree2out<<endl;

	tboardsize = boardsize;
	Game* game = new Game(boardsize);
	UCT* gametree = new UCT(boardsize, debug);
	if(loadone.length() != 0)
		gametree->UCT_Load(loadone);
	UCT* gametree2 = new UCT(boardsize, debug);
	Agent* p1 = new Agent(game, gametree, p1c);
	Agent* p2;
	if(selfplay){ 
		if(loadtwo.length() != 0)
			gametree->UCT_Load(loadtwo);
		p2 = new Agent(game, gametree, p2c);
	} else {
		if(loadtwo.length() != 0)
			gametree2->UCT_Load(loadtwo);
		p2 = new Agent(game, gametree2, p2c);
	}
	game->setDebug(false);
	p1->setDebug(debug);
	p2->setDebug(debug);
	
	p1->setType(p1type);
	p2->setType(p2type);
	p1->setLevel(p1level);
	p2->setLevel(p2level);

	int blackwin = 0, whitewin = 0;
	for(int g = 0; g<gameCounter; g++ ) {
		game->Reset();
		int counter = 0;
		
		cout<<"Starting Game "<<g<<"...\n";
		//create game
		while(!game->Status()) {
			if(pause || debug || !(game->Turn() == -1 ? c1 : c2 )) game->Print();
			if(pause || debug || !(game->Turn() == -1 ? c1 : c2 )) cout<<"Move "<<++counter<<endl;
			//if(debug || pause) cin.ignore();
			//play game
			Coor move(-1,-1);
			
			// alternate moves once agent is ready
			int checker = 0;
			do {
				if(checker > 0)
					if(game->Turn() == -1 ? c1 : c2 ) 
					{
						cout<<"Returned invalid move "<<game->Turn()<<endl;
						for(int i=0; i<(int) game->History().size(); i++)
							cout<<game->History()[i].x<<","<<game->History()[i].y<<endl;
						game->printPrev();
						game->Print();
						exit(0);
					} else {
						cout<<"Invalid Move!"<<endl;
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
		}
		//display result
		if(score || debug || pause) game->Score();
		int result = game->BlackWin();
		if(result < 0) {
			whitewin++;
		} else if (result > 0) {
			blackwin++;
		}
	}

	if(treeout.length() != 0)
		gametree->UCT_Output(treeout);
	if(tree2out.length() != 0 && !selfplay)
		gametree2->UCT_Output(tree2out);
	if(tree2out.length() != 0 && selfplay)
		gametree->UCT_Output(tree2out);
	if(!selfplay && (p2type == 1 || p2type == 2)) cout<<"White Tree size: "<<gametree2->Size()<<endl<<"Black ";
	cout<<"Tree size: "<<gametree->Size()<<endl;
	cout<<"Black Win: "<<blackwin<<endl;
	cout<<"White Win: "<<whitewin<<endl;
	cout<<"Ties: "<<gameCounter - blackwin - whitewin<<endl;
	cout<<"Diffence: "<<abs(blackwin - whitewin)<<endl;
	return 0;
}

void usage_err(string var) {
	if(var.length() > 0) cout<<"Improper usage of '"<<var<<"'"<<endl;
	cout<<"Usage: ./go [-c1 [-type ...] [-level ...]] [-c2 [-type ...] [-level ...]] [-g number_of_games] [-board <size>] [-score] [-selfoff] [-p] [-debug] "<<endl;
	cout<<"\t-board <int>\t-- Changes Boardsize"<<endl;
	cout<<"\t-c1\t\t-- Enable Agent Player 1"<<endl;
	cout<<"\t-c2\t\t-- Enable Agent Player 2"<<endl;
	cout<<"\t-cvar <double>\t-- Set c for UCT"<<endl;
	cout<<"\t-debug\t\t-- Show details of learning"<<endl;
	cout<<"\t-h\t\t-- Displays this menu"<<endl;
	cout<<"\t-level <int>\t-- Depth of tree to search"<<endl;
	cout<<"\t-p\t\t-- Display board after every turn"<<endl;
	cout<<"\t-score\t-- Displays score at the end of game"<<endl;
	cout<<"\t-selfoff\t-- Agents use two different trees"<<endl;
	cout<<"\t-type <int>\t-- 0 Random\n\t\t\t-- 1 UCT Vanilla"<<endl;
	exit(0);
}

Coor getHuman() {
	Coor move(-1,-1);
	char x;
	cout<<"Enter Move: ";
	cin>>x;
	if(x == 'U')
		return Coor(100,100);
	if(x == 'P')
		return move;
	if(x == 'Q') {
		cout<<"Exiting Game..."<<endl;
		exit(0);
	}
	cin>>move.x;
	move.y = (int) x - 'A';
	//cout<<"Move: "<<move.x<<" "<<move.y<<endl;
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