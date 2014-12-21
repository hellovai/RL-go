// Copyright 2014 hellovai

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "../common.h"

#include <iostream>
#include "move.h"
#include "state.h"

class Game {
 private:
  int debug;

  // TODO(hellovai): scoring functions

  // game states
  State *currState;
  State *startState;
  // std::vector<Move *> moveList;
  bool finished;
  int _turn;

 public:
  Game();
  ~Game() {
    delete startState;
    // for (std::vector<Move *>::iterator i = moveList.begin();
    //      i != moveList.end(); ++i) {
    //   delete i;
    // }
  }

  void print() {
    std::cout << "Turn: " << _turn << std::endl;
    std::cout << *currState;
  }

  // getters
  bool isFinished() { return finished; };
  int turn() { return currState->player; };
  int length() { return _turn; };
  // TODO(hellovai): implement
  uint8_t winner() { return currState->player; };

  // setters
  void setDebug(bool debug) { this->debug = debug; }

  // game functions
  std::vector<Move> validMoves();
  bool makeMove(Move *move);
  void undo();
  void redo();
  void reset();
};

#endif
