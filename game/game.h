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

class Game{
	int BOARDSIZE;
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
	bool liberty(Coor );		//finds liberties for a location
	void eat(Coor );			//eats everything with the currect move. Corr is the coordinate of current move.
        void subeat(Coor );
	int* area();				//finds regions of both black and white
	string GetCharPlayer(int ); 	//prints symbol
public:
	Game(int );
	void Print();
	void Reset();
	bool Status() { return my_status; };	//checks if finished
	int Turn() { return current_player; };	//returns current player
	
	bool Move(Coor );						// checks if the coordinate is a valid move
	
	
	int* Score();							// uses area()
     
        //void setboard();                   //test function: initialize the board with a desired pattern.
        //bool liberty(Coor );		//finds liberties for a location
        //void eat(Coor);
};

//=================================
// end guard
#endif
//=================================
