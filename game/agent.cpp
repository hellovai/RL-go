#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

#include "main.h"
#include "game.h"
#include "agent.h"
#include "node.h"
#include "uct.h"

using namespace std;

Agent::Agent( Game* curr_game, UCT* gametree, double inputc ) {
	type = 0;
	level = 82;
	game = curr_game;
	UCTtree = gametree;
	moveData.clear();
	c = inputc;
};

Coor Agent::Move( ) {
	if(debug) cout<<"Starting Move"<<endl;
	switch(type) {
		case 1: //vanilla - random
		case 10: //vanilla - random
		case 13: //vanilla - heuristic
			return UCTSearch();
		case 2:
		case 20: //rave - heuristic
		case 23: //vanilla - heuristic
			return RaveUCTSearch();
		case 3:
			return Heuristic();
		case 0:
		default:
			return Random();
	}
}

//private types
void Agent::GetValidMoves() {
	if(debug) cout<<"Starting GetValidMoves"<<endl;
	moveData.clear();
	moveData.push_back(Coor(-1,-1));
	Item **board = game->board();
	for(int i=0; i<game->Boardsize(); i++)
		for(int j=0; j<game->Boardsize(); j++) {
			if(board[i][j].val == 0 && game->ValidMove(Coor(i,j)))
				moveData.push_back(Coor(i,j));
			//if(debug) cout<<"Checked: "<<i<<","<<j<<endl;
		}
	if(debug) cout<<"Finished searching board "<<moveData.size()<<endl;
	//add passing
}

Coor Agent::Random() {
	if(debug) cout<<"Starting Random"<<endl;
	GetValidMoves();
	return moveData[ rand() % moveData.size()];
}

Coor Agent::Heuristic() {
	if(debug) cout<<"Starting Heuristic"<<endl;
	GetValidMoves();
	vector<int> score;
	for(int j = 0; j < (int) moveData.size(); j++) {
		Game* gametemp = new Game(game->Boardsize());
		vector<Coor> history = game->History();
		for(int i = 0; i < (int) history.size(); i++) {
			gametemp->ValidMove(history[i]);
			gametemp->Move(history[i]);
		}			
		gametemp->ValidMove(moveData[j]);
		gametemp->Move(moveData[j]);
		score.push_back(gametemp->BlackWin());
		//if(debug) gametemp->Print();
		//if(debug) cout<<"Score of move: "<<moveData[j].x<<" "<<moveData[j].y<<" "<<gametemp->BlackWin()<<endl;
	}
	int maxscore = score[0];
	vector<int> index (1, 0);
	for(int i = 1; i < (int) score.size(); i++) {
		if(game->Turn() == -1 && score[i] > maxscore) {
			maxscore = score[i];
			index.clear();
			index.push_back(i);
		} if(game->Turn() == 1 && score[i] < maxscore) {
			maxscore = score[i];
			index.clear();
			index.push_back(i);
		} else if (score[i] == maxscore)
			index.push_back(i);
	}
	//if(debug) cout<<"Done Simulating!"<<endl;
	return moveData[index[rand() % index.size()]];
}

Coor Agent::RaveUCTSearch () {
	if(debug) cout<<"Starting UCTRaveSearch"<<endl;
	Node* curr;
	int i = 0;
	bool nope = true;
	if(debug) cout<<"Staring While Loop"<<endl;
	while(i < level ) {
		curr = RaveSimulate();
		if (debug) cout<<"\t\033[1;31msimulate for Times "<<i<<"\033[0m"<<endl;
		//if(debug) cin.ignore();
		i++;
	}
	if(debug) cout<<"Ending While Loop"<<endl;
	if(debug) curr->Print();
	return RaveSelectMove(curr);
}
Coor Agent::UCTSearch () {
	if(debug) cout<<"Starting UCTSearch"<<endl;
	Node* curr;
	int i = 0;
	bool nope = true;
	if(debug) cout<<"Staring While Loop"<<endl;
	while(i < level ) {
		curr = Simulate();
		if (debug) cout<<"\t\033[1;31msimulate for Times "<<i<<"\033[0m"<<endl;
		//if(debug) cin.ignore();
		i++;
	}
	if(debug) cout<<"Ending While Loop"<<endl;
	if(debug) curr->Print();
	return SelectMove(curr);
}

Node* Agent::RaveSimulate( ) {
	if(debug) cout<<"Starting Rave Simulate"<<endl;
	Game* holder = game;
	vector<Coor> moveHistory = holder->History();
	game = new Game(holder->Boardsize());
	//set board to current position
	game->Reset();
	Node* start = UCTtree->Root();
	Node* relaventpos = start;
	priority.clear();
	for(int j=0; j<(int) moveHistory.size(); j++) {
		if( start == NULL ) {
			cout<<"\tStart was null"<<endl;
			//dump data
			exit(0);
		}
		if(debug) cout<<"Starting node: "<<start->id<<endl;
		int rotater = start->Compare(game->board());
		game->ValidMove(moveHistory[j]);
		game->Move(moveHistory[j]);
		relaventpos = start->Select(mapRotate(moveHistory[j], rotater));
		if(relaventpos != NULL)
			start = relaventpos;
		else {
			if(debug) cout<<"No move history exists!"<<endl;
			for( ; j < (int) moveHistory.size(); j++)
				priority.push_back(moveHistory[j]);
		}
	}
	relaventpos = start;
	if(start == NULL) {
		game->Print();
		cout<<"Starting node is null!"<<endl;
		exit(0);
	}
	// Now position is at current board
	vector<TreeStruct> preferred = RaveSimTree(start); // returns s_0 -> s_t
	int T = game->History().size();
	int z = Default();
	RaveBackUp(T, preferred, z);
	if(debug) cout<<(z == 1 ? "Black wins!" : (z == 0 ? "Tie!" : "White Wins!"))<<endl;
	game = holder;
	return relaventpos;
}
Node* Agent::Simulate( ) {
	if(debug) cout<<"Starting Simulate"<<endl;
	Game* holder = game;
	vector<Coor> moveHistory = holder->History();
	game = new Game(holder->Boardsize());
	//set board to current position
	game->Reset();
	Node* start = UCTtree->Root();
	Node* relaventpos = start;
	priority.clear();
	for(int j=0; j<(int) moveHistory.size(); j++) {
		if( start == NULL ) {
			cout<<"\tStart was null"<<endl;
			//dump data
			exit(0);
		}
		if(debug) cout<<"Starting node: "<<start->id<<endl;
		int rotater = start->Compare(game->board());
		game->ValidMove(moveHistory[j]);
		game->Move(moveHistory[j]);
		relaventpos = start->Select(mapRotate(moveHistory[j], rotater));
		if(relaventpos != NULL)
			start = relaventpos;
		else {
			if(debug) cout<<"No move history exists!"<<endl;
			for( ; j < (int) moveHistory.size(); j++)
				priority.push_back(moveHistory[j]);
		}
	}
	relaventpos = start;
	if(start == NULL) {
		game->Print();
		cout<<"Starting node is null!"<<endl;
		exit(0);
	}

	vector<TreeStruct> preferred = SimTree(start); // returns s_0 -> s_t
	int z = Default();
	BackUp(preferred, z);
	if(debug) cout<<(z == 1 ? "Black wins!" : (z == 0 ? "Tie!" : "White Wins!"))<<endl;
	game = holder;
	return relaventpos;
}

vector<TreeStruct> Agent::RaveSimTree(Node* prev) {
	if(debug) cout<<"Starting Sim Tree"<<endl;
	vector<TreeStruct> reldata;
	Node *curr = prev; //prev->Search(game->board());
	TreeStruct data(NULL, Coor(-1,-1));
	while(!game->Status()) {
		if(curr == NULL) {
			if (debug) cout<<"\tNew node is added"<<endl;
			Coor move = game->History()[game->History().size() - 1];
			int rotater = prev->Compare(game->previous());
			move = mapRotate(move, rotater);
			curr = UCTtree->insert(prev, game->board(), move);
			
			GetValidMoves();
			if(priority.size() == 0) {
				data = curr->RaveSelectMove(c, ConvertOneD(), game->Turn(), 8 );
			} else {
				data.node = NULL;
				data.action = priority[0];
				priority.erase(priority.begin());
			}

			reldata.push_back(TreeStruct(curr, data.action));
			return reldata;
		}
		if(debug) cout <<"\t no new node is added"<<endl;
		
		GetValidMoves();
		int rotater = curr->Compare(game->board());
		if(priority.size() == 0) {
			data = curr->RaveSelectMove( c, ConvertOneD(), game->Turn(), rotater );
		} else {
			data.node = NULL;
			data.action = priority[0];
			priority.erase(priority.begin());
		}
		game->ValidMove(data.action);
		game->Move(data.action);
		if(debug)
			cout<<"\tWill Back up node "<<(curr == NULL ? -100 : curr->id)<<" action "<<data.action.x<<", "<<data.action.y<<endl;;
		reldata.push_back(TreeStruct(curr, data.action));
		prev = curr;
		curr = data.node;
		if(curr == NULL) {
			curr = UCTtree->Search(game->board());
			if(curr != NULL ) {
				prev->addConnect(curr, data.action);
				if(debug) cout<<"Found connection!"<<endl;
				prev->Print();
				curr->Print();
				cin.ignore();
			}
		}
	}
	return reldata;	
}
vector<TreeStruct> Agent::SimTree(Node* prev) {
	if(debug) cout<<"Starting Sim Tree"<<endl;
	vector<TreeStruct> reldata;
	Node *curr = prev; //prev->Search(game->board());
	TreeStruct data(NULL, Coor(-1,-1));
	while(!game->Status()) {
		if(curr == NULL) {
			if (debug) cout<<"\tNew node is added"<<endl;
			Coor move = game->History()[game->History().size() - 1];
			int rotater = prev->Compare(game->previous());
			move = mapRotate(move, rotater);
			curr = UCTtree->insert(prev, game->board(), move);
			data.action = move;
			data.node = curr;
			reldata.push_back(data);
			return reldata;
		}
		if(debug) cout <<"\t no new node is added"<<endl;
		GetValidMoves();
		int rotater = curr->Compare(game->board());
		if(priority.size() == 0) {
			data = curr->SelectMove( c, ConvertOneD(), game->Turn(), rotater );
		} else {
			data.node = NULL;
			data.action = priority[0];
			priority.erase(priority.begin());
		}
		game->ValidMove(data.action);
		game->Move(data.action);
		prev = curr;
		curr = data.node;
		if(curr == NULL) {
			curr = UCTtree->Search(game->board());
			if(curr != NULL ) {
				prev->addConnect(curr, data.action);
				cout<<"Found connection!"<<endl;
				prev->Print();
				curr->Print();
				cin.ignore();
			}
		}
		if(debug)
			cout<<"\tWill Back up node "<<(prev == NULL ? -100 : prev->id)<<" action "<<data.action.x<<", "<<data.action.y<<endl;;
		reldata.push_back(TreeStruct(prev, data.action));
	}
	return reldata;	
}

int Agent::Default() {
	if (debug) cout <<"starting default"<<endl;
	while(!game->Status()) {
		Coor move(-1,-1);
		if(game->Lenght() > 81) {
			//game->setDebug(debug);
			//game->Print();
		}
		switch(type) {
			case 3:
			case 13:
			case 23:
				move = Heuristic();
			case 1:
			case 2:
			case 10:
			case 20:
			default:
				move = Random();
		}
		game->ValidMove(move);
		game->Move(move);
	}
	return game->BlackWin();
}

void Agent::RaveBackUp(int T, vector<TreeStruct> preferred, int win ) {
	if (debug) cout<<"beginning Rave backup"<<endl;
	if(debug) cout <<"\tnode backup size "<<preferred.size()<<endl;
	if(debug) {
		cout<<"\t";
		for(int i=0; i<(int) preferred.size(); i++)
			cout<<(preferred[i].node == NULL ? -100 : preferred[i].node->id)<<" ";
		cout<<endl;
	}
	vector<Coor> history = game->History();
	for(int i=0; i<(int) preferred.size(); i++) {
		Node* current = preferred[i].node;
		if (current==NULL){
	     	if (debug) cout<<"\tpreferred node is empty index "<<i<<endl;
	     		exit (0);
		}
		current->Action(ConvertOneD(preferred[i].action), win);
		
		for(int j=i; j<(int) history.size(); j=j+2) {
			Coor update = history[j];
			bool check = true;
			for(int k=i; k<j-1 && check; k=k+2) {
				if(history[k].x == history[j].x && history[k].y == history[j].y)
					check = false;
			}
			if(check) {
				current->AMAFVisit(ConvertOneD(history[j]));
				current->AMAFAction(ConvertOneD(history[j]), win);
			}
		}
	}
}
void Agent::BackUp( vector<TreeStruct> preferred, int win ) {
	if (debug) cout<<"beginning backup"<<endl;
	if(debug) cout <<"\tnode backup size "<<preferred.size()<<endl;
	if(debug) {
		cout<<"\t";
		for(int i=0; i<(int) preferred.size(); i++)
			cout<<(preferred[i].node == NULL ? -100 : preferred[i].node->id)<<" ";
		cout<<endl;
	}
	for(int i=0; i<(int) preferred.size(); i++) {
		Node* current = preferred[i].node;
		if (current==NULL){
	     	if (debug) cout<<"\tpreferred node is empty index "<<i<<endl;
	     		exit (0);
		} 

		current->Visit();
		if(i<(int) preferred.size() - 1)
			current->Action(ConvertOneD(preferred[i].action), win);
	}
}

Coor Agent::RaveSelectMove(Node* curr) {
	if(debug) cout<<"beginning SelectMove"<<endl;
	//search tree to find node
	GetValidMoves();
	int rotater = curr->Compare(game->board());
	return curr->RaveSelectMove(c, ConvertOneD(), game->Turn(), rotater).action;
}
Coor Agent::SelectMove(Node* curr) {
	if(debug) cout<<"beginning SelectMove"<<endl;
	//search tree to find node
	GetValidMoves();
	int rotater = curr->Compare(game->board());
	return curr->SelectMove( 0.0, ConvertOneD(), game->Turn(), rotater).action;
}

vector<int> Agent::ConvertOneD() {
	//if (debug) cout<<"beginning vector convertoneD"<<endl;
	vector<int> data;
	for(int i=0; i<(int) moveData.size(); i++)
		data.push_back( ( moveData[i].x == -1 || moveData[i].y == -1 ? game->Boardsize()*game->Boardsize() : moveData[i].x*game->Boardsize()+moveData[i].y ) );
	return data;
}

int Agent::ConvertOneD(Coor move ) {
	if (debug) cout<<"beginning int converoneD"<<endl;
	if (move.x == -1 || move.y == -1) return game->Boardsize()*game->Boardsize();
	return move.x*game->Boardsize()+move.y;
}