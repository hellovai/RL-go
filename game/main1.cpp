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
// #include "agent.h"

//int boardsize = 0;

using namespace std;

int main (int argc, char* argv[]) {
	int boardsize = 9;
	bool c1 = false;
	bool c2 = false;
	bool dolog = false;

/*	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if(temp.compare("-b") == 0) {
			if(++i >= argc) usage_err(temp);
			boardsize = atoi(argv[i]);
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
		} else if (temp.compare("-log") == 0) {
			dolog = true;
		} else
			usage_err(temp);
	}*/

	boardsize = max(9, boardsize);
	boardsize = min(boardsize, 19);
/*	// print starting config
	cout<<"Configuration: "<<endl;
	cout<<"\tBoardsize:\t"<<boardsize<<endl;
	cout<<"\tPlayer 1:\t"<<(c1 ? "Agent" : "Human")<<endl;
	cout<<"\tPlayer 2:\t"<<(c2 ? "Agent" : "Human")<<endl;*/
	
	Game* game = new Game(boardsize);
        game->setboard();

        
	//cout<<"Starting Game...\n";
	//create game
	//while(!game->Status())
        game->Print();

        Coor temp;
        cout << "liberty test" << endl;
        for (int i=0; i<=8; i++)
        {
           for (int j=0; j<=8; j++)
           {
              temp.x=i;
              temp.y=j;
              if (game->liberty(temp))
	         cout << "1  ";
              else
                 cout << "0  ";
              
              if (j==8)
                 cout << endl;
           }
        }
        temp.x=8;
        temp.y=8;
        game->eat(temp);
        temp.x=1;
        temp.y=4;
        game->eat(temp);
        temp.x=8;
        temp.y=4;
        game->eat(temp);
        game->Print();
        //test liberty function
        
		
		//play game
	/*	Coor move;
		
		// alternate moves once agent is ready
		// if(game->turn() == -1)
		// 	if(c1) move = agent1->move();
		// 	else move = getHuman();
		// else
		// 	if(c2) move = agent2->move();
		// 	else move = getHuman();
		
		move = getHuman();
		while(!game->Move(move)) {
			cout<<"Sorry, ("<<move.x<<" , "<<move.y<<") is invalid!\n";
			move = getHuman();
		}
	}*/

	//display result
	return 0;
}

void usage_err(string var) {
	cout<<"Improper usage of '"<<var<<"'"<<endl;
	cout<<"Usage: ./go "<<endl;
	exit(0);
}

Coor getHuman() {
	Coor move;
	cout<<"Enter Move: ";
	cin>>move.x>>move.y;
	return move;
}