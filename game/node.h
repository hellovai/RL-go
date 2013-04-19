//=================================
// include guard
#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Node {

	int **board;
	int boardsize;
	int visit;
	bool debug;

	Actiondata* action;
	
	bool Same(int**);
	void Rotate(int, int**);

	void Horizontal(int **);
	void Vertical(int **);
	void RisingDiagonal(int **);
	void FallingDiagonal(int **);
	void Quarter(int **);
	void HalfQuarter(int **);
	void ThreeQuarter(int **);
	double ActionValue( int index, int player, double c );
	int ToOneD(Coor move); 

	public:
		Node(int, Item**, int );
		int Id( ) { return id; };

		int id;
		void Visit();
		void Action(int, int);
		int Compare(Item** );
		Node* Select(Coor );
		treestruct SelectMove( double c, vector<int> legal, int player, int rotater );
		bool addConnect( Node*, Coor );
		void setDebug(bool x ) {debug = x;};
		void Print();
		string GetCharPlayer(int );
};

//=================================
// end guard
#endif
//=================================
