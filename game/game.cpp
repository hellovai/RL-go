#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "main.h"
#include "game.h"

using namespace std;

//public functions
//-1 is black, 1 is white
Game::Game(int boardsize){
	BOARDSIZE = boardsize;
	Reset();
}

void Game::Reset(){
	current_player = -1;
	moves = 0;
	my_status = false;
	black_Count = 181;
	white_Count = 180;
	
    if(BOARDSIZE == 9) {
        black_Count -= 140;
        white_Count -= 140;
    }

    grpCtr = 0;
	grpCheck = BOARDSIZE*BOARDSIZE;
	grpVector.clear();

	Item empty;
	empty.group = 0;
	empty.val = 0;
	empty.visit = false;

	currboard = new Item*[BOARDSIZE];
    prevboard = new Item*[BOARDSIZE];
    futureboard = new Item*[BOARDSIZE];
	for(int i=0;i<BOARDSIZE;i++) {
		currboard[i] = new Item[BOARDSIZE];
		prevboard[i] = new Item[BOARDSIZE];
        futureboard[i] = new Item[BOARDSIZE];
		for(int j=0;j<BOARDSIZE;j++) {
			currboard[i][j] = empty;
            prevboard[i][j] = empty;
            futureboard[i][j] = empty;
		}
	}
	cout<<"Board is ready...\n";
}

void Game::Print(){
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

void Game::printPrev(){
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
void Game::printFuture(){
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
void Game::printGroup(){
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

bool Game::Move ( Coor move ) {
    //special case for passing
    if( (current_player == -1 && black_Count == 0) || (current_player == 1 && white_Count == 0) )
        move = Coor(-1,-1);

    if(move.x == -1 && move.y == -1) {
        if(pass)
            my_status = true;
        else
            pass = true;
        current_player *= -1;
        return true;
    }

	if(!isOk(move))
        return false;
    cout<<"Move is in range"<<endl;

    for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++) {
			futureboard[i][j].val = currboard[i][j].val;
			futureboard[i][j].group = 0;
			futureboard[i][j].visit = false;
		}
	
	if( futureboard[move.x][move.y].val != 0 )
		return false;
	
    cout<<"Move not played"<<endl;

    futureboard[move.x][move.y].val = current_player;
    
    eat(move);

    cout<<"Ate possible peices"<<endl;

	if(!liberty(move))
		return false;
	
    cout<<"Has liberty"<<endl;

	//at this point liberty is kept when this happens
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			if(futureboard[i][j].val != prevboard[i][j].val)
				goto validMove;
    cout<<"Same as prevboard"<<endl;
    printPrev();
    printFuture();
	return false;
	
	validMove:
        pass = false;
        for(int i=0; i<BOARDSIZE; i++)
           for(int j=0; j<BOARDSIZE; j++) {
                prevboard[i][j] = currboard[i][j];
                currboard[i][j] = futureboard[i][j];   
           }
        if(current_player == -1)
            black_Count--;
        else
            white_Count--;

        current_player *= -1;
        
        if(black_Count + white_Count == 0 )
            my_status = true;

		return true;
}

//private functions
string Game::GetCharPlayer(int num){
	switch(num)
	{
		case 1: return "\u25A0";
		case -1: return "\u25A1";
		default: return " ";
	}
}



//finds liberties for a location	
bool Game::liberty(Coor position ){
    if (futureboard[position.x][position.y].val == 0)
        return true;
    for( int i =0; i< 4; i++) {
        Coor nextposition = relativepos(position, i);
        if(!isOk(nextposition)) continue;
        if(futureboard[nextposition.x][nextposition.y].val == 0)
            return true;
        if (futureboard[nextposition.x][nextposition.y].val == futureboard[position.x][position.y].val && !futureboard[nextposition.x][nextposition.y].visit) {
            futureboard[nextposition.x][nextposition.y].visit = true;
            if (liberty(nextposition))
            {
                futureboard[nextposition.x][nextposition.y].visit = false;
                return true;
            }
            futureboard[nextposition.x][nextposition.y].visit = false;
        }
    }
    
    return false;
}

//eats everything with the currect move. Corr is the coordinate of current move.
void Game::eat(Coor position) {
    for( int i =0; i< 4; i++) {
        Coor nextposition = relativepos(position, i);
        if(!isOk(nextposition)) continue;
        if (futureboard[nextposition.x][nextposition.y].val == -1*futureboard[position.x][position.y].val && !liberty(nextposition))
            subeat(nextposition);
    }
    return;
}

void Game::subeat(Coor position) {  
    futureboard[position.x][position.y].visit = true;
    for( int i =0; i< 4; i++) {
        Coor nextposition = relativepos(position, i);
        if(!isOk(nextposition)) continue;
        if (!futureboard[nextposition.x][nextposition.y].visit && futureboard[nextposition.x][nextposition.y].val == futureboard[position.x][position.y].val)
        {
            subeat(nextposition);
            futureboard[nextposition.x][nextposition.y].visit = false;
        }
    }
    futureboard[position.x][position.y].val = 0;
    futureboard[position.x][position.y].visit = false;
    return;
}


//finds regions of both black and white
void Game::area() {
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
    int black = 0, white = 0;
    for (int i=0; i<BOARDSIZE; i++)
        for (int j = 0; j < BOARDSIZE; j++)
        {
            Item curr = futureboard[i][j];
            if(curr.val == -1) black++;
            else if(curr.val == 1) white++;
            else {
                int grp = curr.group;
                if(grpVector[grp-1].type < 0) black++;
                else if(grpVector[grp-1].type > 0) white++;
            }
        }
    cout<<"Score: \n\tBlack: "<<black<<"\n\tWhite: "<<white<<endl;
    printGroup();
}
