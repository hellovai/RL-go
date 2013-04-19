#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "main.h"
#include "node.h"

//Node 
Node::Node(int itemid, Item** currentBoard, int currsize) {
	debug = false;
	id = itemid;
	visit = 0;
	boardsize = currsize;
	board = new int*[boardsize];
	for(int i=0; i<boardsize; i++) {
		board[i] = new int[boardsize];
		for (int j = 0; j < boardsize; j++)
			board[i][j] = currentBoard[i][j].val;
	}
	action = new Actiondata[boardsize*boardsize+1];
	action[boardsize*boardsize].next = this;
	if(debug) cout<<"Initialized Node with id "<<id<<endl;
}

void Node::Visit() {
	if(debug) cout<<"Visiting Node id "<<id<<endl;
	visit++;
}

void Node::Action(int actionid, int win) {
	if(debug) cout<<"Action update Node id "<<id<<endl<<"\tAction "<<actionid<<endl;
	action[actionid].visit++;
	action[actionid].value += ( (double) win - action[actionid].value) / action[actionid].visit;
}

Node* Node::Select( Coor move ) {
	return action[ToOneD(move)].next;
}

int Node::Compare(Item** toCompare) {
	if(debug) cout<<"Comparing with Node id "<<id<<endl;
	int** newboard = new int*[boardsize];
	for(int i=0; i<boardsize; i++) {
		newboard[i] = new int[boardsize];
		for (int j = 0; j < boardsize; j++) {
			newboard[i][j] = toCompare[i][j].val;
		}
	}

		Print();
		
		for(int j=0;j<boardsize;j++)
			cout << ' ' << (char) (j+65);
			cout<<endl;
		for(int i=0;i<boardsize;i++)
		{
			cout<<i<<'\t';
			for(int j=0;j<boardsize;j++)
				cout << '|' << GetCharPlayer(newboard[i][j]);	
				cout << '|' << endl;
		}

	int rotater = 8;
	while(!Same(newboard) && rotater > 1) {
		Rotate(-rotater, newboard);
		Rotate(--rotater, newboard);
	}
	if(!Same(newboard)) {
		Rotate(-rotater, newboard);
		rotater = 8;
		for(int j=0;j<boardsize;j++)
			cout << ' ' << (char) (j+65);
			cout<<endl;
		for(int i=0;i<boardsize;i++)
		{
			cout<<i<<'\t';
			for(int j=0;j<boardsize;j++)
				cout << '|' << GetCharPlayer(newboard[i][j]);	
				cout << '|' << endl;
		}
		cout<<"This should not happen!"<<endl;
		cin.ignore();
	}
	return rotater;
}

TreeStruct Node::SelectMove( double c, vector<int> legal, int player, int rotater ) {
	if(debug) cout<<"Selecing Move from node id "<<id<<" Legal Moves for "<<(player == -1 ? "black" : "white")<<": "<<legal.size()<<endl;
	double key = ActionValue( legal[0], player, c );
	vector<int> index;
	index.push_back(0);
	for( int i = 1; i < (int) legal.size(); i++ )
		if ( player == -1 && ActionValue(legal[i], player, c) > key ) {
			if(debug) {
				//cout<<"\t\tBetter to do "<<legal[i]<<" "<<ActionValue(legal[i], player, c)<<endl;
			}
			index.clear();
			key = ActionValue(legal[i], player, c);
			index.push_back(i);
		} else if (player == 1 && ActionValue(legal[i], player, c) < key ) {
			if(debug) {
				//cout<<"\t\tBetter to do "<<legal[i]<<" "<<ActionValue(legal[i], player, c)<<endl;
			}
			index.clear();
			key = ActionValue(legal[i], player, c);
			index.push_back(i);
		} else if ( ActionValue(legal[i], player, c) == key ) {
			if(debug) {
				//cout<<"\t\tSame to do "<<legal[i]<<" "<<ActionValue(legal[i], player, c)<<endl;
			}
			index.push_back(i);
		} else {
			if(debug) {
				//cout<<"\t\tWorse to do "<<legal[i]<<" "<<ActionValue(legal[i], player, c)<<endl;
			}
		}
	if(debug) cout<<"\tOptions to chose from: "<<index.size()<<endl;
	int selected = legal[index[rand() % index.size()]];
	if(debug) cout<<"\tSelected: "<<selected<<"==> "<<selected / boardsize<<","<< selected % boardsize<<endl;
	TreeStruct data(NULL, Coor(-1,-1));
	data.node = action[selected].next;
	data.action = mapRotate((selected == boardsize*boardsize ? Coor(-1,-1) : Coor(selected / boardsize, selected % boardsize)), rotater);
	if(debug) cout<<"\tPicked action "<<data.action.x<<", "<<data.action.y<<" referring to node "<<(data.node == NULL ? -100 : data.node->id )<<endl;
	return data;
}

bool Node::addConnect( Node* next, Coor move ) {
	if(debug) cout<<"Adding connection for Node id "<<id<<" to "<<next->id<<" "<<move.x<<","<<move.y<<endl;
	if( action[ToOneD(move)].next != NULL )
		return false;
	action[ToOneD(move)].next = next;
	return true;
}

//Private functions
double Node::ActionValue( int i, int player, double c ) {
	//if(debug) cout<<"Updating action "<<i<<" of node id "<<id<<endl;
	return action[i].value + -c*player*( action[i].visit == 0 ? 2 : sqrt( log((double) visit) / action[i].visit )); //since black is -1
}

void Node::Rotate( int rotateid, int** newboard ) {
	if(debug) cout<<"\t";
	if(rotateid < 0 && debug) cout<<"Undo ";
	switch(rotateid) {
		case -1:
		case 1:
			if(debug) cout<<"Horizontal Rotation"<<endl;
			Horizontal(newboard);
			break;
		case 2:
		case -2:
			if(debug) cout<<"Vertical Rotation"<<endl;
			Vertical(newboard);
			break;
		case 3:
		case -3:
			if(debug) cout<<"RisingDiagonal Rotation"<<endl;
			RisingDiagonal(newboard);
			break;
		case 4:
		case -4:
			if(debug) cout<<"FallingDiagonal Rotation"<<endl;
			FallingDiagonal(newboard);
			break;
		case 5:
		case -7:
			if(debug) cout<<"90 Rotation"<<endl;
			Quarter(newboard);
			break;
		case 6:
		case -6:
			if(debug) cout<<"180 Rotation"<<endl;
			HalfQuarter(newboard);
			break;
		case 7:
		case -5:
			if(debug) cout<<"270 Rotation"<<endl;
			ThreeQuarter(newboard);
			break;
		default: // no rotate
			if(debug) cout<<"No Rotation"<<endl;
			return;
	}
}

bool Node::Same(int** newboard) {
	for (int i = 0; i < boardsize; i++)
		for(int j = 0; j < boardsize; j++)
			if( board[i][j] != newboard[i][j]) {
				if(debug) cout<<"Index error at "<<i<<","<<j<<endl;
				return false;
			}
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

int Node::ToOneD(Coor move) {
	if(move.x == -1 || move.y == -1) return boardsize*boardsize;
	return move.x*boardsize+move.y;
}

void Node::Print() {
	for(int j=0;j<boardsize;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<boardsize;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<boardsize;j++)
			cout << '|' << GetCharPlayer(board[i][j]);	
			cout << '|' << endl;
	}
}

string Node::GetCharPlayer(int num) {
	switch(num)
	{
		case 1: return "\u25A0";
		case -1: return "\u25A1";
		default: return " ";
	}
}
