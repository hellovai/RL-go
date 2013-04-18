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

	int id;
	int **board;
	int boardsize;
	int visit;
	
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

		void Visit();
		void Action(int, int);
		int Compare(Item** );
		Node* Select(Coor );
		treestruct SelectMove( double c, vector<int> legal, int player, int rotater );
		bool addConnect( Node*, Coor );
};

struct treestruct{ 
	Node* node;
	Coor action;
};

struct act{
	int visit;
	double value;
	Node* next;
	act() {
		visit = 0;
		value = 0;
		next = NULL;
	}
};

//=================================
// end guard
#endif
//=================================
