//=================================
// include guard
#ifndef __UCT_H_INCLUDED__
#define __UCT_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef struct {
	int* visit;
	int* win;
	Node** next;
	Actiondata(int boardsize) {
		visit = new int[boardsize*boardsize+1];
		win = new int[boardsize*boardsize+1];
		next = new Node*[boardsize*boardsize+1];
		for(int i=0; i<boardsize*boardsize+1; i++) {
			visit[i] = 0;
			win[i] = 0;
			next[i] = NULL;
		}
	}
} Actiondata;

class Node {
	int **board;
	int boardsize;
	
	int win;
	int visit;
	
	Actiondata action(boardsize);
	
	public:
		Node();
}

class UCT {
	Node *root;
	int size;
	
	Node *search(int , Node* );
	void clear_tree(Node* );
	void insert(int , Node* );

	public:
		UCT();
		~UCT();

		void add(Board, Coor );
		void delete(Board );
		Node **search(Coor );
		Node *search(Board );
        void clear_tree();
};

//=================================
// end guard
#endif
//=================================
