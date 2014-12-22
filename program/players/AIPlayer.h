// Copyright 2014 hellovai

#ifndef __AI_PLAYER_H_INCLUDED__
#define __AI_PLAYER_H_INCLUDED__

#include "../common.h"
#include "Player.h"

class AIPlayer : public Player {
 public:
  AIPlayer(Game* g, std::string name) : Player(g, name){};
  ~AIPlayer() {};

  MoveChoice getAction() {
    return MOVE;
  }

  Move* getMove() {
    std::vector<Move*> validMoves;
    _g->validMoves(validMoves);
    int i = rand() % validMoves.size();
    return validMoves[i];
  }
};

#endif
