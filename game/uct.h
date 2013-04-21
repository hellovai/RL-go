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
	bool debug;
	
	Node *search(int , Node* );
//	void clear_tree(Node* );

	public:
		UCT(int, bool );
		~UCT();

		Node* insert(Node* , Item** , Coor );
//		void delete(Item** );
//		Node **search(Coor ); //searches based on if this moved was played -- lower priority
		Node* Search(Item** ); //searches based on variation of this board
//		Node *search(int ); //searches based on ID's
//        void clear_tree();
		Node *Root() {return root;};
		int Size() { return size; };
};


//=================================
// end guard
#endif
//=================================
