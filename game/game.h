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

class Game {
	// add game log
	int BOARDSIZE;
	Item **currboard;
	Item **prevboard;
	Item **prevprevboard;
	Item **futureboard;
	vector<Coor> moveList;

	int current_player; // -1, 1
	int moves;
	bool my_status; 	// if game is over, then this is true
	bool pass;
	bool validpass;
	bool undo;
	bool validundo;

	int black_Count;
	int white_Count;
	
	int grpCtr;
	int grpCheck;
	bool debug;
	
	vector<grpStruct> grpVector;

	//private function
	bool liberty(Coor );		//finds liberties for a location
	void eat(Coor );			//eats everything with the currect move. Corr is the coordinate of current move.
        void subeat(Coor );
	void area();				//finds regions of both black and white
		void getArea(Coor );
	int bonus();
	string GetCharPlayer(int ); 	//prints symbol
	
	//just to make life easier
	bool isOk( Coor );
	bool isOk( int , int );
	Coor relativepos(Coor, int );
	void printFuture();
	void printGroup();
public:
	Game(int );
	Game(Game* );
	~Game();
	void Print();
	void Reset();
	bool Status() { return my_status; };	//checks if finished
	int Turn() { return current_player; };	//returns current player
	Item **board() {return currboard; };
	Item **previous() { return prevboard; };
	Item **prevprevious() { return prevprevboard; };
	int Boardsize() { return BOARDSIZE; };
	void setDebug( bool x ) {debug = x;};
	int Lenght() { return moves; };
	vector<Coor> History() { return moveList; };
    bool Pass() { return pass; };
    bool VPass() { return validpass; };
    bool GUndo() { return undo; };
    bool VUndo() { return validundo; };
    int BCount() { return black_Count; };
    int WCount() { return white_Count; };
	
	bool ValidMove(Coor );					// checks if the coordinate is a valid move
	void Move(Coor );							// makes a move if valid
	
	void Score();							// uses area()
	int BlackWin();
	void printPrev();
	void Undo();
};

//=================================
// end guard
#endif
//=================================
