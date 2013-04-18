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
#include "uct.h"

using namespace std;

Agent::Agent( Game* curr_game, UCT* gametree ) {
	type = 0;
	level = 100;
	game = curr_game;
	UCTtree = gametree;
	moveData.clear();
};

Coor Agent::Move( ) {
	switch(type) {
		case 1: //vanilla
		case 2: //rave
			return UCTSearch();
		case 0:
		default:
			return Random();
	}
}

//private types
void Agent::GetValidMoves() {
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
	GetValidMoves();
	return moveData[ rand() % moveData.size()];
}

Coor Agent::UCTSearch () {
	for(int i=0; i < level; i++) {
		Simulate();
	}
	return SelectMove();
}



void Agent::Simulate( ) {
	Game* holder = game;
	vector<Coor> moveHistory = holder->History();
	game = new Game();
	//set board to current position
	game->Reset();
	Node* start = UCT->Root();
	for(int j=0; j<(int) moveHistory.size(); j++) {
		if( start == NULL ) {
			cout<<"Start was null"<<endl;
			//dump data
			exit(0);
		}
		game->ValidMove(moveHistory[j]);
		game->Move(moveHistory[j]);
		start = start->Select(moveHistory[j]);
	}
	vector<TreeStruct> preferred = SimTree(start); // returns s_0 -> s_t
	int z = Default();
	BackUp(preferred, z);
	game = holder;
}

vector<TreeStruct> Agent::SimTree(Node* prev) {
	vector<TreeStruct> reldata;
	double c = 1.0;
	Node *curr = prev; //prev->Search(game->board());
	TreeStruct data;
	while(!game->Status()) {
		if(curr == NULL) {
			move = game->History()[game->History().size() - 1];
			int rotater = prev->Compare(game->previous());
			move = mapRotate(move, rotater);
			curr = UCT->insert(prev, game->board(), move);
			data.action = move;
			data.node = curr;
			reldata.push_back(data);
			return reldata;
		}
		GetValidMoves();
		data = curr->SelectMove( c, ConvertOneD(moveData), game->Turn(), curr->Compare(game->Board()) );
		game->ValidMove(data.action);
		game->Move(data.action);
		prev = curr;
		curr = data.node;
		reldata.push_back(data);
	}
	return reldata;	
}

int Agent::Default() {
	while(!game->Status()) {
		Coor move;
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
	for(int i=0; i<(int) preferred.size(); i++) {
		Node* current = preferred[i].node;
		current->Visit();
		current->Action(preferred[i].action, win);
	}
}

Coor Agent::SelectMove( ) {
	//search tree to find node
	Node* curr;
	GetValidMoves();
	return curr->SelectMove( 0.0, ConvertOneD(moveData), game->Turn(), curr->Compare(game->Board()) );
}

vector<int> Agent::ConvertOneD() {
	vector<int> data;
	for(int i=0; i<(int) moveData.size(); i++)
		data.push_back( ( moveData[i].x == -1 || moveData[i].y == -1 ? game->Boardsize()*game->Boardsize() : moveData[i].x*game->Boardsize()+moveData[i].y ) );
	return data;
}
