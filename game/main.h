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

typedef struct {
	int x;
	int y;
} Coor;

typedef struct {
	int group;		//used for eating and area, reset to null everytime the board is copied
	int val;		// -1 for black, 1 for white, 0 for empty
	bool visit;		//by default is false
} Item;

Coor getHuman();

//=================================
// end guard
#endif
//=================================
