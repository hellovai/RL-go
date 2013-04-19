#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "main.h"
#include "node.h"
#include "uct.h"

//UCT
UCT::UCT(int bsize, bool dbg) {
	debug = dbg;
	if(debug) cout<<"Init tree"<<endl;
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
	root = new Node(size++, currboard, boardsize);
	root->setDebug(debug);
	if(debug) cout<<"Finished Init tree"<<endl;
}

// Public Functions
Node* UCT::insert(Node* prev, Item** currBoard, Coor move) {
//	Node *prev = search(prevBoard);
//	int rotate = prev->Compare(prevBoard);
	if(debug) cout<<"Inserting Node to "<<prev->id<<"\t"<<move.x<<", "<<move.y<<endl<<"\tCurrent size: "<<size<<endl;
	Node *next = new Node(size++, currBoard, boardsize);
	next->setDebug(debug);
	if(!prev->addConnect(next, move)) {
		cout<<"\n\nInserting with  tree did not connect"<<endl;
		//dump data
		exit(0);
	}
	if(debug) cout<<" New size: "<<size<<endl;
	return next;
}

//Private Functions
