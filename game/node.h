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
	double RaveActionValue( int index, int player, double c );
	int ToOneD(Coor move); 

	public:
		Node(int, Item**, int );
		Node(int, int );
		int Id( ) { return id; };

		int **board;
		int id;
		void Visit();
		void Action(int, int);
		void AMAFVisit(int);
		void AMAFAction(int, int);
		int Compare(Item** );
		Node* Select(Coor );
		Node* Select(int );
		treestruct SelectMove( double c, vector<int> legal, int player, int rotater );
		treestruct RaveSelectMove( double c, vector<int> legal, int player, int rotater );
		bool addConnect( Node*, Coor );
		void setDebug(bool x ) {debug = x;};
		void Print();
		string GetCharPlayer(int );

		//for read and write only
		int getVisit();
		int getVisit(int );
		int getAMAFVisit(int );
		double getValue(int );
		double getAMAFValue(int );
		void Load(int, Node*, int, double, int, double);
		void setBoard(int** );
		void setVisit(int );
};

//=================================
// end guard
#endif
//=================================
