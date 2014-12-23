// Copyright 2014 hellovai

#ifndef __AI_PLAYER_H_INCLUDED__
#define __AI_PLAYER_H_INCLUDED__

#include "../common.h"
#include "Player.h"
#include "Brain.h"

class AIPlayer : public Player {
 protected:
  Brain* _b;
  virtual void needed() = 0;

 public:
  AIPlayer(Game* g, std::string name) : Player(g, name){};
  ~AIPlayer() { delete _b; };

  MoveChoice getAction() { return MOVE; }

  Move* getMove() {
    std::vector<Move*> validMoves;
    _g->validMoves(validMoves);
    int i = _b->think(validMoves, _g);
    return Move::list[i];
  }
};

class RandomAIPlayer : public AIPlayer {
  void needed(){};

 public:
  RandomAIPlayer(Game* g, std::string name) : AIPlayer(g, name) {
    _b = new RandomBrain();
  };
};

class UCTAIPlayer : public AIPlayer {
  void needed(){};

 public:
  UCTAIPlayer(Game* g, std::string name) : AIPlayer(g, name) {
    _b = new UCTBrain();
  };
};

#endif
