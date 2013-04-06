#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "main.h"
#include "game.h"

using namespace std;

//public functions
//-1 is black, 1 is white
Game::Game(int boardsize){
	BOARDSIZE = boardsize;
	Reset();
}

void Game::Reset(){
	current_player = -1;
	moves = 0;
	my_status = false;

	black_Count = 181;
	white_Count = 180;
	black_Capture = 0;
	white_Capture = 0;
	grpCtr = 0;
	grpCheck = NULL;
	
	Item empty;
	empty.group = NULL;
	empty.val = 0;
	empty.visit = false;

	currboard = new Item*[BOARDSIZE];
	prevboard = new Item*[BOARDSIZE];
	for(int i=0;i<BOARDSIZE;i++) {
		currboard[i] = new Item[BOARDSIZE];
		prevboard[i] = new Item[BOARDSIZE];
		for(int j=0;j<BOARDSIZE;j++) {
			currboard[i][j] = empty;
			prevboard[i][j] = empty;
		}
	}
	cout<<"Board is ready...\n";
}

void Game::Print(){
	cout<<'\t';
	for(int j=0;j<BOARDSIZE;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<BOARDSIZE;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<BOARDSIZE;j++)
			cout << '|' << GetCharPlayer(currboard[i][j].val);	
			cout << '|' << endl;
	}
}

bool Game::Move ( Coor move ) {
	Item **futureboard;
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++) {
			futureboard[i][j] = curr_board[i][j];
			futureboard[i][j].group = NULL;
			futureboard[i][j].visit = false;
		}
	
	if( futureboard[move.x][move.y].val != 0 )
		return false;
	
	if(!liberty(move))
		return false;
	
	//at this point liberty is kept when this happens
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			if(futureboard[i][j] != prevboard[i][j])
				goto pass;
	return false;
	
	pass:
		prevboard = currboard;
		currboard = futureboard;
		return true;
}

//private functions
string Game::GetCharPlayer(int num){
	switch(num)
	{
		case -1: return "\u25A0";
		case 1: return "\u25A1";
		default: return " ";
	}
}

//finds liberties for a location, default takes in current_player
bool Game::liberty(Coor ) {
	return false;
}

//finds liberties for a location	
bool Game::liberty(int, Coor ){
	return false;
}

//eats everything with the group number of the Coordinate
void Game::eat(Coor ) {
	return;
}


//finds regions of both black and white
int* Game::area() {
	for( int i=0; i<BOARDSIZE; i++ )
		for(int j = 0; j<BOARDSIZE; j++)
			if(currboard[i][j].group == NULL && currboard[i][j].val == 0) {
				Coor move;
				move.x = i;
				move.y = j;
				getArea(Coor(i,j));
			}
			
	return NULL;
}

void getArea(Coor move) {
	//this peice should already have a group id set, if not then set to group count and increment group counter
	Item *curr = &currboard[move.x][move.y], other;
	curr.visit = true;
	
	if(curr.group == NULL) {
		curr.group == grpCtr++;
		grpChk = NULL;
	}
	
	switch( curr.val ) {
		case 1:
		case -1:
			//this should never happen
			return;
		default:
			for(int i =0; i<3; i++) {
				Coor temp;
				switch(i) {
					case 0:
						temp.y = move.y;
						temp.x = move.x-1;
						break;
					case 1:
						temp.y = move.y;
						temp.x = move.x+1;
						break;
					case 2:
						temp.y = move.y-1;
						temp.x = move.x;
						break;
					case 3:
						temp.y = move.y+1;
						temp.x = move.x;
						break;
				}
				if(!isOk(temp))
					continue;
				other = &currboard[temp.x][temp.y];
				if(!other.visit && other.val == 0) {
					other.group = grpCtr;
					getArea(temp);
				} else if ( other.val != 0 ) {
					if(grpCheck == NULL)
						grpCheck = other.val;
					else if (grpCheck = 0 || abs( grpCheck + other.val ) < abs(grpCheck) )
						grpCheck = 0;
					else
						grpCheck += other.val;
				}
			}
	}
	return;
}

bool Game::isOk( Coor move ) {
	if(move.x < 0 || move.x >= BOARDSIZE || move.y < 0 || move.y >= BOARDSIZE)
		return false;
	return true;
}

bool Game::isOk( int i, int j ) {
	if(i < 0 || i >= BOARDSIZE || j < 0 || j >= BOARDSIZE)
		return false;
	return true;
}