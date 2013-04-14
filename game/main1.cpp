#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

int boardsize = 10;

using namespace std;

void RisingDiagonal( int** newboard );
void Print(int ** newboard);

int main (int argc, char* argv[]) {
	int** board = new int*[boardsize];
	for(int i=0; i<boardsize; i++) {
		board[i] = new int[boardsize];
		for(int j=0; j<boardsize; j++)
			board[i][j] = rand() % 2;
	}
	Print(board);
	RisingDiagonal(board);
	Print(board);
}

void RisingDiagonal( int** newboard ) {
	for (int i = 0; i < boardsize/2; i++)
		for(int j = 0; j < boardsize; j++) {
			int temp = newboard[i][j];
			newboard[i][j] = newboard[boardsize-i-1][j];
			newboard[boardsize-i-1][j] = temp;
		}
}

void Print(int ** newboard ) {
	for(int i=0; i<boardsize; i++) {
		for(int j=0; j<boardsize; j++)
			cout<<newboard[i][j]<<"|";
		cout<<endl;
	}
	cout<<"__________________"<<endl;
}