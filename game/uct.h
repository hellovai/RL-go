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

class UCT {
	Node *root;
	int size;
	int boardsize;
	
	Node *search(int , Node* );
//	void clear_tree(Node* );

	public:
		UCT(int );
		~UCT();

		void insert(Item**, Coor );
//		void delete(Item** );
//		Node **search(Coor ); //searches based on if this moved was played -- lower priority
//		Node *search(Item** ); //searches based on variation of this board
//		Node *search(int ); //searches based on ID's
//        void clear_tree();
		Node *Root() {return root;};
};


//=================================
// end guard
#endif
//=================================
