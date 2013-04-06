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
	black_Capture = 0;
	white_Capture = 0;
	grpCtr = 0;
	grpCheck = NULL;
	
	Item empty;
	empty.group = NULL;
	empty.val = 0;
	empty.visit = false;

	currboard = new Item*[BOARDSIZE];
	prevboard = new Item*[BOARDSIZE];
	for(int i=0;i<BOARDSIZE;i++) {
		currboard[i] = new Item[BOARDSIZE];
		prevboard[i] = new Item[BOARDSIZE];
		for(int j=0;j<BOARDSIZE;j++) {
			currboard[i][j] = empty;
			prevboard[i][j] = empty;
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

bool Game::Move ( Coor move ) {
	Item **futureboard;
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++) {
			futureboard[i][j] = curr_board[i][j];
			futureboard[i][j].group = NULL;
			futureboard[i][j].visit = false;
		}
	
	if( futureboard[move.x][move.y].val != 0 )
		return false;
	
	if(!liberty(move))
		return false;
	
	//at this point liberty is kept when this happens
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			if(futureboard[i][j] != prevboard[i][j])
				goto pass;
	return false;
	
	pass:
		prevboard = currboard;
		currboard = futureboard;
		return true;
}

//private functions
string Game::GetCharPlayer(int num){
	switch(num)
	{
		case -1: return "\u25A0";
		case 1: return "\u25A1";
		default: return " ";
	}
}


//finds liberties for a location	
bool Game::liberty(Coor position ){
    if (currboard[position.x][position.y].val == 0)
            return true;
    Coor nextposition;
    nextposition = position;
    
    if (position.x < BOARDSIZE -1)
    {
            if (currboard[position.x + 1][position.y].val==0)
                return true;
            if (currboard[position.x][position.y].val == currboard[position.x + 1][position.y].val)
	      {
                if (!currboard[position.x + 1][position.y].visit)
                {
                    currboard[position.x + 1][position.y].visit = true;
                    nextposition=position;
                    nextposition.x++;
                    if (liberty(nextposition))
                    {
                        currboard[position.x + 1][position.y].visit = false;
                        return true;
                    }
                    currboard[position.x + 1][position.y].visit = false;
                }
	      }
    }
    
    if (position.x > 0)
    {
            if (currboard[position.x - 1][position.y].val==0)
                return true;
            if (currboard[position.x][position.y].val == currboard[position.x - 1][position.y].val)
	      {
                if (!currboard[position.x - 1][position.y].visit)
                {
                    currboard[position.x - 1][position.y].visit = true;
                    nextposition=position;
                    nextposition.x--;
                    if (liberty(nextposition))
                    {
                        currboard[position.x - 1][position.y].visit = false;
                        return true;
                    }
                    currboard[position.x - 1][position.y].visit = false;
                }
	      }
    }
    
    if (position.y < BOARDSIZE -1)
    {
            if (currboard[position.x][position.y + 1].val==0)
                return true;
            if (currboard[position.x][position.y].val == currboard[position.x][position.y + 1].val)
	      {
                if (!currboard[position.x][position.y + 1].visit)
                {
                    currboard[position.x][position.y + 1].visit = true;
                    nextposition=position;
                    nextposition.y++;
                    if (liberty(nextposition))
                    {
                        currboard[position.x][position.y + 1].visit = false;
                        return true;
                    }
                    currboard[position.x][position.y + 1].visit = false;
                }
	      }
    }
    
     if (position.y > 0)
    {
            if (currboard[position.x][position.y - 1].val==0)
                return true;
            if (currboard[position.x][position.y].val == currboard[position.x][position.y - 1].val)
	      {
                if (!currboard[position.x][position.y - 1].visit)
                {
                    currboard[position.x][position.y - 1].visit = true;
                    nextposition=position;
                    nextposition.y--;
                    if (liberty(nextposition))
                    {
                        currboard[position.x][position.y - 1].visit = false;
                        return true;
                    }
                    currboard[position.x][position.y - 1].visit = false;
                }
	      }
    }
    
    return false;
}

//eats everything with the currect move. Corr is the coordinate of current move.
void Game::eat(Coor position) {
    Coor nextposition;
    if (position.x < BOARDSIZE -1)
    {
        if (currboard[position.x + 1][position.y].val != currboard[position.x][position.y].val)
        {
            nextposition=position;
            nextposition.x++;
            if (!liberty(nextposition))
            {
                subeat(nextposition);
            }
        }
    }
    
    if (position.x > 0)
    {
        if (currboard[position.x - 1][position.y].val != currboard[position.x][position.y].val)
        {
            nextposition=position;
            nextposition.x--;
            if (!liberty(nextposition))
            {
                subeat(nextposition);
            }
        }
    }
    
    if (position.y < BOARDSIZE -1)
    {
        if (currboard[position.x][position.y + 1].val != currboard[position.x][position.y].val)
        {
            nextposition=position;
            nextposition.y++;
            if (!liberty(nextposition))
            {
                subeat(nextposition);
            }
        }
    }
    
    if (position.y > 0)
    {
        if (currboard[position.x][position.y - 1].val != currboard[position.x][position.y].val)
        {
            nextposition=position;
            nextposition.y--;
            if (!liberty(nextposition))
            {
                subeat(nextposition);
            }
        }
    }
    
    return;
}

void Game::subeat(Coor position) {  
    currboard[position.x][position.y].visit = true;
    Coor nextposition;
    if (position.x < BOARDSIZE -1)
    {
        if (currboard[position.x + 1][position.y].val == currboard[position.x][position.y].val)
        {
	  if (!currboard[position.x + 1][position.y].visit)
	    {
               nextposition=position;
               nextposition.x++;
               currboard[nextposition.x][nextposition.y].visit = true;
               subeat(nextposition);
               currboard[nextposition.x][nextposition.y].visit = false;
	    }

        }
    }
    if (position.x > 0)
    {
        if (currboard[position.x - 1][position.y].val == currboard[position.x][position.y].val)
        {
	  if (!currboard[position.x -1][position.y].visit)
	    {
               nextposition=position;
               nextposition.x--;
               currboard[nextposition.x][nextposition.y].visit = true;
               subeat(nextposition);
               currboard[nextposition.x][nextposition.y].visit = false;
	    }
        }
    }
    if (position.y < BOARDSIZE -1)
    {
        if (currboard[position.x][position.y+1].val == currboard[position.x][position.y].val)
        {
	  if (!currboard[position.x][position.y+1].visit)
	    {
               nextposition=position;
               nextposition.y++;
               currboard[nextposition.x][nextposition.y].visit = true;
               subeat(nextposition);
               currboard[nextposition.x][nextposition.y].visit = false;
	    }
        }
    }
    if (position.y > 0)
    {
        if (currboard[position.x][position.y-1].val == currboard[position.x][position.y].val)
        {
	  if (!currboard[position.x][position.y-1].visit)
	    {
               nextposition=position;
               nextposition.x++;
               currboard[nextposition.x][nextposition.y].visit = true;
               subeat(nextposition);
               currboard[nextposition.x][nextposition.y].visit = false;
	    }
        }
    }
    currboard[position.x][position.y].val = 0;
    currboard[position.x][position.y].visit = false;
    return;
}


//finds regions of both black and white
int* Game::area() {
	for( int i=0; i<BOARDSIZE; i++ )
		for(int j = 0; j<BOARDSIZE; j++)
			if(currboard[i][j].group == NULL && currboard[i][j].val == 0) {
				Coor move;
				move.x = i;
				move.y = j;
				getArea(Coor(i,j));
			}
			
	return NULL;
}

//test function: initialize the board with a desired function
/*void Game::setboard(){
     currboard[0][0].val=0;
     currboard[0][1].val=0;
     currboard[0][2].val=1;
     currboard[0][3].val=1;
     currboard[0][4].val=-1;
     currboard[0][5].val=1;
     currboard[0][6].val=-1;
     currboard[0][7].val=1;
     currboard[0][8].val=0;
     currboard[1][0].val=-1;
     currboard[1][1].val=0;
     currboard[1][2].val=1;
     currboard[1][3].val=1;
     currboard[1][4].val=-1;
     currboard[1][5].val=1;
     currboard[1][6].val=0;
     currboard[1][7].val=1;
     currboard[1][8].val=-1;
     currboard[2][0].val=-1;
     currboard[2][1].val=-1;
     currboard[2][2].val=1;
     currboard[2][3].val=1;
     currboard[2][4].val=1;
     currboard[2][5].val=1;
     currboard[2][6].val=0;
     currboard[2][7].val=1;
     currboard[2][8].val=0;
     currboard[3][0].val=0;
     currboard[3][1].val=0;
     currboard[3][2].val=1;
     currboard[3][3].val=-1;
     currboard[3][4].val=1;
     currboard[3][5].val=1;
     currboard[3][6].val=0;
     currboard[3][7].val=1;
     currboard[3][8].val=-1;
     currboard[4][0].val=0;
     currboard[4][1].val=0;
     currboard[4][2].val=1;
     currboard[4][3].val=1;
     currboard[4][4].val=-1;
     currboard[4][5].val=1;
     currboard[4][6].val=0;
     currboard[4][7].val=1;
     currboard[4][8].val=1;
     currboard[5][0].val=-1;
     currboard[5][1].val=0;
     currboard[5][2].val=-1;
     currboard[5][3].val=1;
     currboard[5][4].val=0;
     currboard[5][5].val=1;
     currboard[5][6].val=-1;
     currboard[5][7].val=1;
     currboard[5][8].val=-1;
     currboard[6][0].val=0;
     currboard[6][1].val=-1;
     currboard[6][2].val=1;
     currboard[6][3].val=-1;
     currboard[6][4].val=0;
     currboard[6][5].val=1;
     currboard[6][6].val=0;
     currboard[6][7].val=1;
     currboard[6][8].val=-1;
     currboard[7][0].val=0;
     currboard[7][1].val=-1;
     currboard[7][2].val=1;
     currboard[7][3].val=-1;
     currboard[7][4].val=0;
     currboard[7][5].val=1;
     currboard[7][6].val=1;
     currboard[7][7].val=1;
     currboard[7][8].val=-1;
     currboard[8][0].val=0;
     currboard[8][1].val=-1;
     currboard[8][2].val=1;
     currboard[8][3].val=1;
     currboard[8][4].val=1;
     currboard[8][5].val=-1;
     currboard[8][6].val=-1;
     currboard[8][7].val=-1;
     currboard[8][8].val=-1;
return;
}*/

void getArea(Coor move) {
	//this peice should already have a group id set, if not then set to group count and increment group counter
	Item *curr = &currboard[move.x][move.y], other;
	curr.visit = true;
	
	if(curr.group == NULL) {
		curr.group == grpCtr++;
		grpChk = NULL;
	}
	
	switch( curr.val ) {
		case 1:
		case -1:
			//this should never happen
			return;
		default:
			for(int i =0; i<3; i++) {
				Coor temp;
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
				if(!isOk(temp))
					continue;
				other = &currboard[temp.x][temp.y];
				if(!other.visit && other.val == 0) {
					other.group = grpCtr;
					getArea(temp);
				} else if ( other.val != 0 ) {
					if(grpCheck == NULL)
						grpCheck = other.val;
					else if (grpCheck = 0 || abs( grpCheck + other.val ) < abs(grpCheck) )
						grpCheck = 0;
					else
						grpCheck += other.val;
				}
			}
	}
	return;
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

