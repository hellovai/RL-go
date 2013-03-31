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
Game::Game(){
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
	
	for(int i=0;i<BOARDSIZE;i++)
		for(int j=0;j<BOARDSIZE;j++) {
			currboard[i][j] = empty;
			prevboard[i][j] = empty;
		}
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
			if(board[i][j] != 0)
				cout << '|' << GetCharPlayer(board[i][j]);	
			else
				cout << '|' << GetCharPlayer(board[i][j]);
			cout << '|' << endl;
	}
}

bool Game::Move ( Coor move ) {
	return false;
}

//private functions
char Game::GetCharPlayer(int num){
	switch(num)
	{
		case -1: return '\u25A0';
		case 1: return '\u25A1';
		default: return ' ';
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
	return false;
}


//finds regions of both black and white
int* Game::area() {
	return NULL;
}