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

Agent::Agent( Game* curr_game ) {
	type = 0;
	game = curr_game;
	//movelist = new UCT();
	moveData.clear();
};

Coor Agent::Move( ) {
	Item **board = game->board();
	moveData.clear();
	for(int i=0; i<game->Boardsize(); i++)
		for(int j=0; j<game->Boardsize(); j++)
			if(board[i][j].val == 0 && game->ValidMove(Coor(i,j)))
				moveData.push_back(Coor(i,j));
	//add passing
	moveData.push_back(Coor(-1,-1));
	
	int index;
	
	switch(type) {
		case 1:
			index = UCTVanilla();
			break;
		case 0:
		default:
			index = Random();
			break;
	}
	return moveData[index];
}

/*void Agent::Update( ) {
	//get results of game
	//update based on type
	switch(type) {
		case 1:
			UCTUpdate();
		case 0:
		default:
			break;
	}
}*/

//private types
int Agent::Random() {
	return rand() % moveData.size();
}

int Agent::UCTVanilla () {
	return rand() % moveData.size();
}