// Copyright 2014 hellovai

#ifndef __GAMECONTAINER_H_INCLUDED__
#define __GAMECONTAINER_H_INCLUDED__

#include "game/game.h"
#include "players/Player.h"

class GameContainer {
  Game* _g;
  Player* _p[3];
  bool _r;

 public:
  GameContainer(Game* g, Player* p1 = nullptr, Player* p2 = nullptr) : _g(g) {
    _p[0] = nullptr;
    _p[1] = p1;
    _p[2] = p2;
  }
  ~GameContainer() {}

  void start(int turns = -1) {
    while (!_g->isFinished() && turns-- != 0) {
      Player* p = _p[_g->turn()];
      MoveChoice choice = p->getAction();
      if (choice == REDO)
        _g->redo();
      else if (choice == UNDO)
        _g->undo();
      else if (choice == MOVE) {
        Move* m = new Move();
        p->getMove(m);
        _g->makeMove(m);
      } else if (choice == QUIT)
        return;
    }
  }
};

#endif
