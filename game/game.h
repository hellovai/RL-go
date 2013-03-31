//=================================
// include guard
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef struct {
	int x;
	int y;
} Coor;

typedef struct {
	int group;		//used for eating and area, reset to null everytime the board is copied
	int val;		// -1 for black, 1 for white, 0 for empty
	bool visit;		//by default is false
} Item;

extern BOARDSIZE;

class Game{
	Item ** currboard;
	Item ** prevboard;
	
	int current_player; // -1, 1
	int moves;
	bool my_status; 	// if game is over, then this is true

	int black_Count;
	int white_Count;
	int black_Capture;
	int white_Capture;
	
	//private function
	bool liberty(Coor );		//finds liberties for a location, default takes in current_player
	bool liberty(int, Coor );	//finds liberties for a location
	void eat(Coor );			//eats everything with the group number of the Coordinate
	int* area();					//finds regions of both black and white

public:
	Game(int);
	void Print();
	void Reset();
	bool Status() { return my_status; };	//checks if finished
	int Turn() { return current_player; };	//returns current player
	
	bool Move(Coor );						// checks if the coordinate is a valid move
	
	
	int* Score();							// uses area()
};

//=================================
// end guard
#endif
//=================================