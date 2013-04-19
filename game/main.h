//=================================
// include guard
#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void usage_err(string );

typedef struct treestruct TreeStruct;
typedef struct coorStruct Coor;
typedef struct struct1 Item;
typedef struct grpStuff grpStruct;
typedef struct act Actiondata;
class UCT;
class Node;
class Game;
class Agent;

struct coorStruct {
	int x;
	int y;
	
	coorStruct(int xInt, int yInt) : x(xInt), y(yInt) { };
	coorStruct();
};

struct struct1{
	int group;		//used for eating and area, reset to null everytime the board is copied
	int val;		// -1 for black, 1 for white, 0 for empty
	bool visit;		//by default is false
};

struct grpStuff{
	int numb;
	int type;
	grpStuff(int xInt, int yInt) : numb(xInt), type(yInt) { }
};

struct treestruct{ 
	Node* node;
	Coor action;
	treestruct() {
		node = NULL;
		action = Coor(-1,-1);
	};
	treestruct(Node* next, Coor arb) : node(next), action(arb) { };
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

Coor getHuman();
Coor mapRotate(Coor, int);
//=================================
// end guard
#endif
//=================================
