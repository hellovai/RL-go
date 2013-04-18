#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "node.h"
#include "uct.h"

//UCT
UCT::UCT(int bsize) {
	boardsize = bsize;
	size = 0;
	//Start with empty board
	Item empty;
	empty.group = 0;
	empty.val = 0;
	empty.visit = false;
	Item** currboard;
	currboard = new Item*[boardsize];
	for(int i=0;i<boardsize;i++) {
		currboard[i] = new Item[boardsize];
		for(int j=0;j<boardsize;j++)
			currboard[i][j] = empty;
	}
	
	root = new Node(size++, currentBoard, boardsize);
}

// Public Functions
void UCT::insert(Node* prev, Item** currBoard, Coor move) {
//	Node *prev = search(prevBoard);
//	int rotate = prev->Compare(prevBoard);
	Node *next = new Node(size++, currBoard, boardsize);
	if(!prev->addConnect(next, move)) {
		cout<<"Inserting with  tree had weird stuff"<<endl;
		//dump data
		exit(0);
	}
}

//Private Functions
