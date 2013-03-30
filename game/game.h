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

	int ** board;
	int current_player;
	int moves;
	bool my_status;


public:
	Game(int);
	void Print();
	void Reset();

};

//=================================
// end guard
#endif
//=================================