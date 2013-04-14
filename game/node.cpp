#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "main.h"
#include "node.h"

//Node 
Node::Node(int itemid, Item** currentBoard, int currsize)) {
	id = itemid;
	visit = 0;
	boardsize = currsize;
	board = new int*[boardsize];
	for(int i=0; i<boardsize; i++) {
		board[i] = new int[boardsize];
		for (int j = 0; j < boardsize; j++)
			board[i][j] = currentBoard[i][j].val;
	}
	action = new ActionData[boardsize*boardsize+1];
	action[boardsize*boardsize].node = this;
}

void Node::Visit() {
	visit++;
}

void Node::Action(int actionid, int win) {
	action.visit[actionid]++;
	action.value[actionid] += ( (double) win - action.value[actionid]) / action.visit[actionid];
}

int Node::Compare(Item** toCompare) {
	int** newboard = new int*[boardsize];
	for(int i=0; i<boardsize; i++) {
		newboard[i] = new int[boardsize];
		for (int j = 0; j < boardsize; j++)
			newboard[i][j] = toCompare[i][j].val;
	}
	int rotater = 1;
	Rotate(rotater, newboard);
	while(!Same(newboard) && rotater < 8) {
		Rotate(-rotater, newboard);
		Rotate(++rotater, newboard);
	}
	return rotater;
}

TreeStruct Node::Select( double c, vector<int> legal, int player, int rotater ) {
	double key = ActionValue( legal[0], player, c );
	vector<int> index = {0};
	for( int i = 0; i < (int) legal.size(); i++ )
		if ( player == -1 && ActionValue(legal[i], player, c) > key ) {
			index.clear();
			key = ActionValue(legal[i], player, c);
			index.push_back(i);
		} else if (player == 1 && ActionValue(legal[i], player, c) < key ) {
			index.clear();
			key = ActionValue(legal[i], player, c);
			index.push_back(i);
		} else if ( ActionValue(legal[i], player, c) == key ) {
			index.push_back(i);
		}
	TreeStruct data;
	int selected = index[rand() % index.size()];
	data.node = action[ selected ].node;

	if( id == boardsize*boardsize ) data.action = Coor(-1,-1);
	else {
		int x = id / boardsize, y = id % boardsize;
		switch (rotater) {
			case 1:
				data.action = Coor( x, boardsize-1-y ); break;
			case 2:
				data.action = Coor( boardsize-1-x, y ); break;
			case 3:
				data.action = Coor( y, x ); break;
			case 4:
				data.action = Coor( boardsize-1-y, boardsize-1-x ); break;
			case 5:
				data.action = Coor( boardsize-1-y, x ); break;
			case 6:
				data.action = Coor( boardsize-1-x, boardsize-1-y ); break;
			case 7:
				data.action = Coor( y, boardsize-1-x ); break;
			default:
				data.action = Coor( x, y); break;
		}
	}
	return data;
}

//Private functions
double Node::ActionValue( int index, int player, double c ) {
	return action[i].value + c*player*(-1)*sqrt*( log((double) visit) / action[i].visit ); //since black is -1
}

void Node::Rotate( int rotateid, int** newboard ) {
	switch(rotateid) {
		case 1:
		case -1:
			Horizontal(newboard);
			break;
		case 2:
		case -2:
			Vertical(newboard);
			break;
		case 3:
		case -3:
			RisingDiagonal(newboard);
			break;
		case 4:
		case -4:
			FallingDiagonal(newboard);
			break;
		case 5:
		case -7:
			Quarter(newboard);
			break;
		case 6:
		case -6:
			HalfQuarter(newboard);
			break;
		case 7:
		case -5:
			ThreeQuarter(newboard);
			break;
		default: // no rotate
			return;
	}
}

bool Node::Same(int** newboard) {
	for (int i = 0; i < boardsize; i++)
		for(int j = 0; j < boardsize; j++)
			if( board[i][j] != newboard[i][j])
				return false;
	return true;
}

// Symmetry stuff
void Node::Horizontal( int** newboard ) {
	for (int i = 0; i < boardsize/2; i++)
		for(int j = 0; j < boardsize; j++) {
			int temp = newboard[i][j];
			newboard[i][j] = newboard[boardsize-i-1][j];
			newboard[boardsize-i-1][j] = temp;
		}
}

void Node::Vertical( int** newboard ) {
	for (int i = 0; i < boardsize; i++)
		for(int j = 0; j < boardsize/2; j++) {
			int temp = newboard[i][j];
			newboard[i][j] = newboard[i][boardsize-j-1];
			newboard[i][boardsize-j-1] = temp;
		}
}

void Node::RisingDiagonal( int** newboard ) {
	for (int i = 0; i < boardsize; i++)
		for(int j = 0; j < i; j++) {
			int temp = newboard[i][j];
			newboard[i][j] = newboard[j][i];
			newboard[j][i] = temp;
		}
}

void Node::FallingDiagonal( int** newboard ) {
	RisingDiagonal(newboard);
	Horizontal(newboard);
	Vertical(newboard);
}

void Node::Quarter( int** newboard ) {
	RisingDiagonal(newboard);
	Horizontal(newboard);
}

void Node::HalfQuarter( int** newboard ) {
	Vertical(newboard);
	Horizontal(newboard);
}

void Node::ThreeQuarter( int** newboard ) {
	RisingDiagonal(newboard);
	Vertical(newboard);
}
