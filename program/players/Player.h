// Copyright 2014 hellovai

#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "../common.h"
#include "../game/game.h"
#include <string>

enum MoveChoice { MOVE = 1, UNDO, REDO, QUIT, COUNT };

std::istream& operator>>(std::istream& is, MoveChoice& i) {
  int tmp;
  while (!(is >> tmp)) {
    is.clear();
    is.ignore(INT_MAX, '\n');
  }
  i = static_cast<MoveChoice>(tmp);
  return is;
}

class Player {
 protected:
  Game* _g;
  std::string _name;

 public:
  Player(Game* g, std::string name) : _g(g), _name(name) {}
  virtual ~Player() {}

  virtual MoveChoice getAction() = 0;
  virtual Move* getMove() = 0;
};

class Human : public Player {
 public:
  Human(Game* g, std::string name) : Player(g, name) {}
  ~Human() {}

  MoveChoice getAction() {
    MoveChoice choice = COUNT;
    _g->print();
    do {
      std::cout << _name << " select action\n"
                << "1. Move\n"
                << "2. Undo\n"
                << "3. Redo\n"
                << "4. Quit" << std::endl << "Select: ";
      std::cin >> choice;
    } while (!(choice < COUNT));
    return choice;
  }

  Move* getMove() {
    Move m;
    std::cin >> m;
    return Move::fetch(m);
  }
};

#endif
