// Copyright 2014 hellovai

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <glog/logging.h>
#include <iostream>
#include "move.h"
#include "state.h"

class Game {
  private:
    int debug;

    // game states
    State *currState;
    State *startState;
    bool finished;

  public:
    Game();
    ~Game() {}

    void print() {
      std::cout << *currState;
    }

    // getters
    bool isFinished() {
      return finished;
    };
    int turn() {
      return currState->player;
    };
    int length() {
      return currState->turn;
    };
    // TODO(hellovai): implement
    uint8_t winner() {
      return currState->player;
    };

    // setters
    void setDebug(bool debug) {
      this->debug = debug;
    }

    // game functions
    boost::dynamic_bitset<> validMoves();
    bool makeMove(Move* move);
    void undo();
    void redo();
    void reset();
};

#endif


