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

typedef struct {
	int visit;
	double value;
	Node* next;
	Actiondata() {
		visit = 0;
		value = 0;
		next = NULL;
	}
} Actiondata;

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
	double Node::ActionValue( int index, int player, double c );

	public:
		Node(int, Item**, int );
		int Id( ) { return id; };

		void Visit();
		void Action(int, int);
		int Compare(Item** );
		Node* Select(double );
		TreeStruct SelectMove( double c, vector<int> legal, int player, int rotater );
};


//=================================
// end guard
#endif
//=================================
