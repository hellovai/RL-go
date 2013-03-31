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
	return false;
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
	return NULL;
}