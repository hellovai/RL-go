#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

#include "main.h"
#include "node.h"
#include "uct.h"

using namespace std;
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
	Node *next = new Node(size++, currboard, boardsize);
	next->setDebug(debug);
	next->addConnect(root, Coor(-1,-1));
	root->addConnect(next, Coor(-1,-1));
	if(debug) cout<<"Finished Init tree"<<endl;
}

// Public Functions
Node* UCT::insert(Node* prev, Item** currBoard, Coor move) {
//	Node *prev = search(prevBoard);
//	int rotate = prev->Compare(prevBoard);
	if(debug) cout<<"Inserting Node to "<<prev->id<<"\t"<<move.x<<", "<<move.y<<endl<<"\tCurrent size: "<<size<<endl;
	Node *next = new Node(size++, currBoard, boardsize);
	Node *nextpt2 = new Node(size++, currBoard, boardsize);
	next->setDebug(debug);
	nextpt2->setDebug(debug);
	next->addConnect(nextpt2, Coor(-1,-1));
	nextpt2->addConnect(next, Coor(-1,-1));
	if(!prev->addConnect(next, move)) {
		cout<<"\n\nInserting with  tree did not connect"<<endl;
		//dump data
		exit(0);
	}
	if(debug) cout<<" New size: "<<size<<endl;
	return next;
}

Node* UCT::Search(Item** board) {
	queue<Node *> searchlist;
	searchlist.push(root);
	vector<int> idlist (1, root->id);
	while(!searchlist.empty()) {
		Node* curr = searchlist.front();
		if(curr->Compare(board) != -1)
			return curr;
		for( int i = 0; i < boardsize*boardsize+1; i++ ) {
			Node* next = curr->Select(i);
			if(next != NULL) {
				if( find(idlist.begin(), idlist.end(), next->id) != idlist.end() ) {
					searchlist.push(next);
					idlist.push_back(next->id);
				}
			}
		}
		searchlist.pop();
	}
	return NULL;
}

void UCT::UCT_Output(string filename) {
	string name = filename + "_connect.dat";
	oconnection.open(name.c_str());
	name = filename + "_board.dat";
	oboard.open(name.c_str());
	name = filename + ".cfg";
	oconfig.open(name.c_str());
	oconfig<<size<<endl;
	oconfig<<boardsize<<endl;
	oconfig.close();

	queue<Node *> nodelist;
	nodelist.push(root);
	bool* idlist = new bool[size];
	for(int i = 0; i<size; i++)
		idlist[i] = false;

	idlist[root->id] = true;
	while(!nodelist.empty()) {
		Node* curr = nodelist.front();
		UCT_Write_Connect(curr);
		if ( curr->id % 2 == 0 ) 
			UCT_Write_Board(curr); //so we dont waste space writing two boards that are the same

		for( int i = 0; i < boardsize*boardsize+1; i++ ) {
			Node* next = curr->Select(i);
			if(next != NULL) {
				if( !idlist[next->id] ) {
					nodelist.push(next);
					idlist[next->id] = true;
				}
			}
		}
		nodelist.pop();
	}
	oconnection.close();
	oboard.close();
}

void UCT::UCT_Write_Board(Node* current)
{
	int i, j;
	oboard << current->id<<endl;
	oboard << current->getVisit() << endl;
	oboard << current->Select(boardsize*boardsize)->getVisit() << endl;
	for (i=0; i<boardsize; i++) {
		for (j=0; j<boardsize; j++)
			oboard << current->board[i][j] << " ";
		oboard<<endl;
	}
}
void UCT::UCT_Write_Connect(Node* current){
	if (current == NULL)
		return;
	int i, j;
	for (i=0; i<=boardsize*boardsize;i++){

		if (current->Select(i) != NULL)
		{		
			oconnection << current->id << " ";
			oconnection << i << " ";
			oconnection << current->Select(i)->id<<" ";
			oconnection << current->getVisit(i)<<" ";
			oconnection << current->getValue(i)<<" ";
			oconnection << current->getAMAFVisit(i)<<" ";
			oconnection << current->getAMAFValue(i)<<endl;
		}
	}
}

void UCT::UCT_Load(string filename) {
	string name = filename + ".cfg";
	iconfig.open(name.c_str());
	if (iconfig)
	{
		iconfig >> size >> boardsize;
		iconfig.close();
	}
	
	name = filename + "_connect.dat";
	iconnection.open(name.c_str());

	Node **tree_array=new Node *[size];
	for(int i = 0; i<size; i++)
		tree_array[i] = new Node(i, boardsize);
	root = tree_array[0];
	if (iconnection) {
		while(!iconnection.eof()) {
			int id, action, next, visit, amafvisit;
			double value, amafvalue;
			iconnection >>  id >> action >> next >> visit >> value >> amafvisit >> amafvalue;
			tree_array[id]->Load(action, tree_array[next], visit, value, amafvisit, amafvalue);
		}
		iconnection.close();
	}
	name = filename + "_board.dat";
	iboard.open(name.c_str());
	int ** temp_board = new int*[boardsize];
	for(int i = 0; i<boardsize; i++)
		temp_board[i] = new int[boardsize];
	if (iboard) {
		for(int k = 0; k <size / 2 ; k++) {
			int id, visit, nextvisit;
			iboard >> id >> visit >> nextvisit;
			tree_array[id]->setVisit(visit);
			tree_array[id+1]->setVisit(nextvisit);
			for(int i = 0; i<boardsize; i++)
				for(int j = 0; j<boardsize; j++)
					iboard >> temp_board[i][j];
			tree_array[id]->setBoard(temp_board);
			tree_array[id+1]->setBoard(temp_board);
		}
		iboard.close();
	}	
	for (int i = 0; i < boardsize; i++)
  		delete[]temp_board[i];
	delete[]temp_board;
	delete[]tree_array;
}




//Private Functions
string UCT::GetCharPlayer(int num) {
	switch(num)
	{
		case 1: return "\u25A0";
		case -1: return "\u25A1";
		default: return " ";
	}
}

int UCT::GetIntPlayer(string num) {
	if( num.compare("\u25A0") == 0 ) return 1;
	else if ( num.compare("\u25A0") == 0 ) return -1;
	return 0;
}
