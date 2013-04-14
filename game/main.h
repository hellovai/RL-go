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

typedef struct coorStruct{
	int x;
	int y;
	coorStruct(int xInt, int yInt) : x(xInt), y(yInt) { }
} Coor;

typedef struct {
	int group;		//used for eating and area, reset to null everytime the board is copied
	int val;		// -1 for black, 1 for white, 0 for empty
	bool visit;		//by default is false
} Item;

typedef struct grpStuff{
	int numb;
	int type;
	grpStuff(int xInt, int yInt) : numb(xInt), type(yInt) { }
} grpStruct;

typedef struct { 
	Node* node;
	int action;
} TreeStruct;


Coor getHuman();
//=================================
// end guard
#endif
//=================================
