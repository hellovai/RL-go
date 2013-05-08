#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>

#include "main.h"
#include "game.h"

using namespace std;

//public functions
//-1 is black, 1 is white
Game::Game(Game* other) {
	BOARDSIZE = other->Boardsize();
	current_player = other->Turn();
	moves = other->Lenght();
	my_status = false;
	moveList = other->History();

	pass = other->Pass();
	validpass = other->VPass();
	undo = other->GUndo();
	validundo = other->VUndo();
	black_Count = other->BCount();
	white_Count = other->WCount();
	debug = false;
	
	// if(BOARDSIZE == 9) {
		// black_Count -= 140;
		// white_Count -= 140;
	// }

	grpCtr = 0;
	grpCheck = BOARDSIZE*BOARDSIZE;
	grpVector.clear();

	Item empty;
	empty.group = 0;
	empty.val = 0;
	empty.visit = false;

	currboard = new Item*[BOARDSIZE];
	prevboard = new Item*[BOARDSIZE];
	prevprevboard = new Item*[BOARDSIZE];
	futureboard = new Item*[BOARDSIZE];
	for(int i=0;i<BOARDSIZE;i++) {
		currboard[i] = new Item[BOARDSIZE];
		prevboard[i] = new Item[BOARDSIZE];
		prevprevboard[i] = new Item[BOARDSIZE];
		futureboard[i] = new Item[BOARDSIZE];
		for(int j=0;j<BOARDSIZE;j++) {
			currboard[i][j] = other->board()[i][j];
			prevboard[i][j] = other->previous()[i][j];
			prevprevboard[i][j] = other->prevprevious()[i][j];
			futureboard[i][j] = empty;
		}
	}
	if(debug) cout<<"Board is ready...\n";
}

Game::~Game() {
	for (int i = 0; i < BOARDSIZE; i++) {
		delete[]currboard[i];
		delete[]prevboard[i];
		delete[]prevprevboard[i];
		delete[]futureboard[i];
	}
	delete[]currboard;
	delete[]prevboard;
	delete[]prevprevboard;
	delete[]futureboard;
}

Game::Game(int boardsize) {
	BOARDSIZE = boardsize;
	Reset();
}

void Game::Reset() {
	current_player = -1;
	moves = 0;
	my_status = false;
	pass = false;
	validpass = false;
	undo = false;
	validundo = false;
	black_Count = PEICEMAX;
	white_Count = PEICEMAX;
	moveList.clear();
	debug = false;
	
	// if(BOARDSIZE == 9) {
		// black_Count -= 140;
		// white_Count -= 140;
	// }

	grpCtr = 0;
	grpCheck = BOARDSIZE*BOARDSIZE;
	grpVector.clear();

	Item empty;
	empty.group = 0;
	empty.val = 0;
	empty.visit = false;

	currboard = new Item*[BOARDSIZE];
	prevboard = new Item*[BOARDSIZE];
	prevprevboard = new Item*[BOARDSIZE];
	futureboard = new Item*[BOARDSIZE];
	for(int i=0;i<BOARDSIZE;i++) {
		currboard[i] = new Item[BOARDSIZE];
		prevboard[i] = new Item[BOARDSIZE];
		prevprevboard[i] = new Item[BOARDSIZE];
		futureboard[i] = new Item[BOARDSIZE];
		for(int j=0;j<BOARDSIZE;j++) {
			currboard[i][j] = empty;
			prevboard[i][j] = empty;
			prevprevboard[i][j] = empty;
			futureboard[i][j] = empty;
		}
	}
	if(debug) cout<<"Board is ready...\n";
}

void Game::Print() {
	cout<<'\t';
	for(int j=0;j<BOARDSIZE;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<BOARDSIZE;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<BOARDSIZE;j++)
			cout << '|' << GetCharPlayer(currboard[i][j].val);	
			cout << '|' << endl;
	}
}

void Game::printPrev() {
	cout<<'\t';
	for(int j=0;j<BOARDSIZE;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<BOARDSIZE;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<BOARDSIZE;j++)
			cout << '|' << GetCharPlayer(prevboard[i][j].val);  
			cout << '|' << endl;
	}
}
void Game::printFuture() {
	cout<<'\t';
	for(int j=0;j<BOARDSIZE;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<BOARDSIZE;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<BOARDSIZE;j++)
			cout << '|' << GetCharPlayer(futureboard[i][j].val);  
			cout << '|' << endl;
	}
}
void Game::printGroup() {
	cout<<'\t';
	for(int j=0;j<BOARDSIZE;j++)
		cout << ' ' << (char) (j+65);
		cout<<endl;
	for(int i=0;i<BOARDSIZE;i++)
	{
		cout<<i<<'\t';
		for(int j=0;j<BOARDSIZE;j++)
			if(futureboard[i][j].val == 0)  cout << '|' << futureboard[i][j].group;
			else cout << '|' << GetCharPlayer(futureboard[i][j].val);  
			cout << '|' << endl;
	}
	for(int i =0; i< (int) grpVector.size(); i++)
		cout<<grpVector[i].numb<<"\t|\t";
		cout<<endl;
	for(int i =0; i< (int) grpVector.size(); i++)
		cout<<grpVector[i].type<<"\t|\t";
		cout<<endl;
}

bool Game::ValidMove ( Coor move ) {
	//special case for passing
	if(move.x == 100 && move.y == 100 && !undo) {
		undo = true;
		validundo = true;
		return true;
	}
	if( (current_player == -1 && black_Count == 0) || (current_player == 1 && white_Count == 0) )
		move = Coor(-1,-1);
	if(move.x == -1 && move.y == -1) {
		if(pass)
			my_status = true;
		else
			pass = true;
		validpass = true;
		return true;
	}

	if(!isOk(move))
		return false;
	if(debug) cout<<"Move is in range"<<endl;

	if( currboard[move.x][move.y].val != 0 )
		return false;

	if(debug) cout<<"Move not played"<<endl;
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++) {
			futureboard[i][j].val = currboard[i][j].val;
			futureboard[i][j].group = 0;
			futureboard[i][j].visit = false;
		}
	

	futureboard[move.x][move.y].val = current_player;
	
	eat(move);

	if(debug) cout<<"Ate possible peices"<<endl;

	if(!liberty(move))
		return false;
	
	if(debug) cout<<"Has liberty"<<endl;

	//at this point liberty is kept when this happens
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			if(futureboard[i][j].val != prevboard[i][j].val)
				return true;
	return false;
}

void Game::Move(Coor move) {
	if(undo && validundo)
		Undo();
	else {
		if(!validpass) {
			pass = false;
			for(int i=0; i<BOARDSIZE; i++)
			   for(int j=0; j<BOARDSIZE; j++) {
					prevprevboard[i][j] = prevboard[i][j];
					prevboard[i][j] = currboard[i][j];
					currboard[i][j] = futureboard[i][j];   
			   }
			if(current_player == -1)
				black_Count--;
			else
				white_Count--;
		} else {
			if(debug) cout<<(current_player == -1 ? "Black" : "White")<<" Passed!"<<endl;
		}
			moveList.push_back(move);
			validpass = false;
			current_player *= -1;
			moves++;
			undo = false;
			validundo = false;
			if(debug) cout<<"Turn of: "<<(current_player == -1 ? "Black" : "White")<<endl;
	}
}

void Game::Undo()
{
	current_player *= -1;
	moves--;
	if (!pass)
	{
		for(int i=0; i<BOARDSIZE; i++)
		   for(int j=0; j<BOARDSIZE; j++) {
				currboard[i][j] = prevboard[i][j];   
				prevboard[i][j] = prevprevboard[i][j];
		   }
		if(current_player == -1)
			black_Count++;
		else
			white_Count++;
	}
	else if(my_status)
		my_status = false;
	else
		pass = false;
	//cout<<"Pass is: "<<pass<<endl;
	//cout<<"Status is: "<<my_status<<endl;
	moveList.pop_back();
	validundo = false;
}

//private functions
string Game::GetCharPlayer(int num) {
	switch(num)
	{
		case 1: return "\u25A0";
		case -1: return "\u25A1";
		default: return " ";
	}
}



//finds liberties for a location	
bool Game::liberty(Coor position ) {
	queue<Coor> searchlist;
	searchlist.push(position);
	bool set = false;
	while(!searchlist.empty() && !set) {
		Coor curr = searchlist.front();
		if( futureboard[curr.x][curr.y].val == 0)
			set=true;
		for( int i = 0; i < 4; i++ ) {
			Coor nextposition = relativepos(curr, i);
			if(isOk(nextposition))
				if(!futureboard[nextposition.x][nextposition.y].visit && futureboard[nextposition.x][nextposition.y].val != -1*futureboard[curr.x][curr.y].val) {
					futureboard[nextposition.x][nextposition.y].visit = true;
					searchlist.push(nextposition);
				}
		}
		searchlist.pop();
	}
	for(int i = 0; i < BOARDSIZE; i++ )
		for(int j = 0; j < BOARDSIZE; j++ )
			futureboard[i][j].visit = false;

	return set;
}

//eats everything with the currect move. Corr is the coordinate of current move.
void Game::eat(Coor position) {
	for( int i =0; i< 4; i++) {
		Coor nextposition = relativepos(position, i);
		if(isOk(nextposition))
			if (futureboard[nextposition.x][nextposition.y].val == -1*futureboard[position.x][position.y].val && !liberty(nextposition))
				subeat(nextposition);
	}
	return;
}

void Game::subeat(Coor position) {
	queue<Coor> searchlist;
	searchlist.push(position);
	while(!searchlist.empty()) {
		Coor curr = searchlist.front();
		for( int i = 0; i < 4; i++ ) {
			Coor nextposition = relativepos(curr, i);
			if(isOk(nextposition))
				if(!futureboard[nextposition.x][nextposition.y].visit && futureboard[nextposition.x][nextposition.y].val == futureboard[curr.x][curr.y].val) {
					futureboard[nextposition.x][nextposition.y].visit = true;
					searchlist.push(nextposition);
				}
		}
		futureboard[curr.x][curr.y].val = 0;
		futureboard[curr.x][curr.y].visit = false;
		searchlist.pop();
	}
}


//finds regions of both black and white
void Game::area() {
	grpVector.clear();
	grpCtr = 0;
	for( int i = 0; i < BOARDSIZE; i++)
		for(int j = 0; j<BOARDSIZE; j++) {
			futureboard[i][j].val = currboard[i][j].val;
			futureboard[i][j].visit = false;
	}
	for( int i=0; i<BOARDSIZE; i++ )
		for(int j = 0; j<BOARDSIZE; j++)
			if(futureboard[i][j].group == 0 && futureboard[i][j].val == 0) {
				getArea(Coor(i,j));
				if(grpCheck == BOARDSIZE*BOARDSIZE)
					grpCheck = 0;
				grpVector.push_back(grpStruct(grpCtr, grpCheck));
				grpCheck = BOARDSIZE*BOARDSIZE;
			}
}

void Game::getArea(Coor move) {
	//this peice should already have a group id set, if not then set to group count and increment group counter
	futureboard[move.x][move.y].visit = true;
	
	if(futureboard[move.x][move.y].group == 0) {
		futureboard[move.x][move.y].group = ++grpCtr;
		grpCheck = BOARDSIZE*BOARDSIZE;
	}
	
	for(int i =0; i<4; i++) {
		Coor temp = relativepos(move, i);
		if(!isOk(temp))
			continue;
		if( !futureboard[temp.x][temp.y].visit && futureboard[temp.x][temp.y].val == 0 ) {
			futureboard[temp.x][temp.y].group = grpCtr;
			getArea(temp);
		} else if ( futureboard[temp.x][temp.y].val != 0 ) {
			if(grpCheck == BOARDSIZE*BOARDSIZE)
				grpCheck = futureboard[temp.x][temp.y].val;
			else if (grpCheck == 0 || abs( grpCheck + futureboard[temp.x][temp.y].val ) < abs(grpCheck) )
				grpCheck = 0;
			else
				grpCheck += futureboard[temp.x][temp.y].val;
		}
	}
}

bool Game::isOk( Coor move ) {
	if(move.x < 0 || move.x >= BOARDSIZE || move.y < 0 || move.y >= BOARDSIZE)
		return false;
	return true;
}

bool Game::isOk( int i, int j ) {
	if(i < 0 || i >= BOARDSIZE || j < 0 || j >= BOARDSIZE)
		return false;
	return true;
}

Coor Game::relativepos(Coor move, int i) {
	Coor temp(-1,-1);
	switch(i) {
		case 0:
			temp.y = move.y;
			temp.x = move.x-1;
			break;
		case 1:
			temp.y = move.y;
			temp.x = move.x+1;
			break;
		case 2:
			temp.y = move.y-1;
			temp.x = move.x;
			break;
		case 3:
			temp.y = move.y+1;
			temp.x = move.x;
			break;
	}
	return temp;
}

void Game::Score( ) {
	area();
	int black = 0, white = bonus(), boardblack = 0, boardwhite = 0;
	for (int i=0; i<BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			Item curr = futureboard[i][j];
			if(curr.val == -1) boardblack++;
			else if(curr.val == 1) boardwhite++;
			else {
				int grp = curr.group;
				if(grpVector[grp-1].type < 0) black++;
				else if(grpVector[grp-1].type > 0) white++;
			}
		}
		black += (PEICEMAX-white_Count)-boardwhite;
		white += (PEICEMAX-black_Count)-boardblack;	
		if(black < 0 || white < 0) {
			black++;
			white++;
		}
	cout<<"Score: \n\tBlack: "<<black<<"\n\tWhite: "<<white<<endl;
	cout<<"Number of Moves: "<<moves<<endl;
	cout<<"Black Used: "<<PEICEMAX-black_Count<<endl;
	cout<<"White Used: "<<PEICEMAX-white_Count<<endl;
	printGroup();
}

int Game::BlackWin() {   
	area();
	int black = 0, white = bonus(), boardblack = 0, boardwhite = 0;
	for (int i=0; i<BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			Item curr = futureboard[i][j];
			if(curr.val == -1) boardblack++;
			else if(curr.val == 1) boardwhite++;
			else {
				int grp = curr.group;
				if(grpVector[grp-1].type < 0) black++;
				else if(grpVector[grp-1].type > 0) white++;
			}
		}
	black += (PEICEMAX-white_Count)-boardwhite;
	white += (PEICEMAX-black_Count)-boardblack;
	return black - white;
}

int Game::bonus( ) {
	if (BOARDSIZE < 10) return 0;
	// else if (BOARDSIZE < 8) return 1;
	// else if (BOARDSIZE < 10) return 1;
	// else if (BOARDSIZE < 15) return 3; 
	else if (BOARDSIZE < 17) return 6;
	else return 8;
}