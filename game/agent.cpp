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
#include "node.h"
#include "uct.h"

using namespace std;

Agent::Agent( Game* curr_game, UCT* gametree ) {
	type = 0;
	level = 82;
	game = curr_game;
	UCTtree = gametree;
	moveData.clear();
};

Coor Agent::Move( ) {
	if(debug) cout<<"Starting Move"<<endl;
	switch(type) {
		case 1: //vanilla
		case 2: //rave
			if(debug) cout<<"Beginning UCT Search:"<<endl;
			return UCTSearch();
		case 0:
		default:
			return Random();
	}
}

//private types
void Agent::GetValidMoves() {
	//if(debug) cout<<"Starting GetValidMoves"<<endl;
	moveData.clear();
	Item **board = game->board();
	for(int i=0; i<game->Boardsize(); i++)
		for(int j=0; j<game->Boardsize(); j++)
			if(board[i][j].val == 0 && game->ValidMove(Coor(i,j)))
				moveData.push_back(Coor(i,j));
	//add passing
	moveData.push_back(Coor(-1,-1));
}

Coor Agent::Random() {
	//if(debug) cout<<"Starting Random"<<endl;
	GetValidMoves();
	return moveData[ rand() % moveData.size()];
}

Coor Agent::UCTSearch () {
	if(debug) cout<<"Starting UCTSearch"<<endl;
	Node* curr;
	int i = 0;
	bool nope = true;
	if(debug) cout<<"Staring While Loop"<<endl;
	while(i < level && nope) {
		curr = Simulate();
		if (debug) cout<<"\t\033[1;31msimulate for Times "<<i++<<"\033[0m"<<endl;
		//if(debug) cin.ignore();
		if( i == level ) {
			cout<<"We are done!"<<endl;
			nope = false;
		}
	}
	if(debug) cout<<"Ending While Loop"<<endl;
	curr->Print();
	return SelectMove(curr);
}



Node* Agent::Simulate( ) {
	if(debug) cout<<"Starting Simulate"<<endl;
	Game* holder = game;
	vector<Coor> moveHistory = holder->History();
	game = new Game(holder->Boardsize());
	//set board to current position
	game->Reset();
	Node* start = UCTtree->Root();
	Node* relaventpos = start;
	for(int j=0; j<(int) moveHistory.size(); j++) {
		if( start == NULL ) {
			cout<<"\tStart was null"<<endl;
			//dump data
			exit(0);
		}
		if(debug) cout<<"Starting node: "<<start->id<<endl;
		int rotater = start->Compare(game->board());
		game->ValidMove(moveHistory[j]);
		game->Move(moveHistory[j]);
		start = start->Select(mapRotate(moveHistory[j], rotater));
	}
	relaventpos = start;
	if(start == NULL) {
		game->Print();
		cout<<"Starting node is null!"<<endl;
		exit(0);
	}
	vector<TreeStruct> preferred = SimTree(start); // returns s_0 -> s_t
	int z = Default();
	BackUp(preferred, z);
	if(debug) cout<<(z == 1 ? "Black wins!" : (z == 0 ? "Tie!" : "White Wins!"))<<endl;
	game = holder;
	return relaventpos;
}

vector<TreeStruct> Agent::SimTree(Node* prev) {
	if(debug) cout<<"Starting Sim Tree"<<endl;
	vector<TreeStruct> reldata;
	double c = 1.0;
	Node *curr = prev; //prev->Search(game->board());
	TreeStruct data(NULL, Coor(-1,-1));
	while(!game->Status()) {
		if(curr == NULL) {
			if (debug) cout<<"\tNew node is added"<<endl;
			Coor move = game->History()[game->History().size() - 1];
			int rotater = prev->Compare(game->previous());
			move = mapRotate(move, rotater);
			curr = UCTtree->insert(prev, game->board(), move);
			data.action = move;
			data.node = curr;
			reldata.push_back(data);
			return reldata;
		}
		if(debug) cout <<"\t no new node is added"<<endl;
		GetValidMoves();
		int rotater = curr->Compare(game->board());
		data = curr->SelectMove( c, ConvertOneD(), game->Turn(), rotater );
		game->ValidMove(data.action);
		game->Move(data.action);
		prev = curr;
		curr = data.node;
		if(debug)
			cout<<"\tWill Back up node "<<(prev == NULL ? -100 : prev->id)<<" action "<<data.action.x<<", "<<data.action.y<<endl;;
		reldata.push_back(TreeStruct(prev, data.action));
	}
	return reldata;	
}

int Agent::Default() {
	if (debug) cout <<"starting default"<<endl;
	while(!game->Status()) {
		Coor move(-1,-1);
		switch(type) {
			case 1:
			default:
				move = Random();
		}
		game->ValidMove(move);
		game->Move(move);
	}
	return game->BlackWin();
}

void Agent::BackUp( vector<TreeStruct> preferred, int win ) {
	if (debug) cout<<"beginning backup"<<endl;
	if(debug) cout <<"\tnode backup size "<<preferred.size()<<endl;
	if(debug) {
		cout<<"\t";
		for(int i=0; i<(int) preferred.size(); i++)
			cout<<(preferred[i].node == NULL ? -100 : preferred[i].node->id)<<" ";
		cout<<endl;
	}
	for(int i=0; i<(int) preferred.size(); i++) {
		Node* current = preferred[i].node;
		if (current==NULL){
	     	if (debug) cout<<"\tpreferred node is empty index "<<i<<endl;
	     		exit (0);
		} 

		current->Visit();
		if(i<(int) preferred.size() - 1)
			current->Action(ConvertOneD(preferred[i].action), win);
	}

}

Coor Agent::SelectMove(Node* curr) {
	if(debug) cout<<"beginning SelectMove"<<endl;
	//search tree to find node
	GetValidMoves();
	int rotater = curr->Compare(game->board());
	cout<<"Node"<<endl;
	curr->Print();
	cout<<"Current"<<endl;
	game->Print();
	cout<<"previous"<<endl;
	game->printPrev();
	cout<<"Rotater: "<<rotater<<endl;
	return curr->SelectMove( 0.0, ConvertOneD(), game->Turn(), rotater).action;
}

vector<int> Agent::ConvertOneD() {
	//if (debug) cout<<"beginning vector convertoneD"<<endl;
	vector<int> data;
	for(int i=0; i<(int) moveData.size(); i++)
		data.push_back( ( moveData[i].x == -1 || moveData[i].y == -1 ? game->Boardsize()*game->Boardsize() : moveData[i].x*game->Boardsize()+moveData[i].y ) );
	return data;
}

int Agent::ConvertOneD(Coor move ) {
	if (debug) cout<<"beginning int converoneD"<<endl;
	if (move.x == -1 || move.y == -1) return game->Boardsize()*game->Boardsize();
	return move.x*game->Boardsize()+move.y;
}