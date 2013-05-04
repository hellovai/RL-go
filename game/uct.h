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
	ofstream oconnection, oboard, oconfig; 
	ifstream iconnection, iboard, iconfig; 

	Node *search(int , Node* );
	void UCT_Write_Board(Node*  );
	void UCT_Write_Connect(Node*  );
	string GetCharPlayer(int );
	int GetIntPlayer(string);
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
		void UCT_Output(string );
		void UCT_Load(string );
};


//=================================
// end guard
#endif
//=================================
