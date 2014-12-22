// Copyright 2014 hellovai

#ifndef __MOVE_H_INCLUDED__
#define __MOVE_H_INCLUDED__
#include "../common.h"

#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <vector>

typedef enum {
  TOP = 1,
  BOT = 2,
  RIGHT = 3,
  LEFT = 4,
  NUM_SIDES,
} Side;

class Move {
 public:
  static int maxMoveSize;
  static std::vector<Move*> list;
  int x;
  int y;
  bool pass;

  int index;

  Move() : pass(true), x(-1), y(-1) {
    index = pass ? maxMoveSize * maxMoveSize : x * maxMoveSize + y;
  }
  explicit Move(Move* curr)
      : x(curr->x), y(curr->y), pass(curr->pass), index(curr->index) {}

  Move(int x_, int y_) : x(x_), y(y_) {
    pass = x < 0 || y < 0;
    index = pass ? maxMoveSize * maxMoveSize : x * maxMoveSize + y;
  }
  explicit Move(int i) : index(i) {
    x = index / maxMoveSize;
    y = index % maxMoveSize;
    pass = index == maxMoveSize * maxMoveSize;
  }

  void setIndex() {
    index = pass ? maxMoveSize * maxMoveSize : x * maxMoveSize + y;
  }

  void reset(int i) {
    index = i;
    x = index / maxMoveSize;
    y = index % maxMoveSize;
    pass = index == maxMoveSize * maxMoveSize;
  }

 public:
  ~Move() {}

  static void fill(int b, int e) {
    for (int i = b; i < e; ++i) list.push_back(new Move(i));
  }

  static void unfill() {
    for (int i = 0; i < list.size(); ++i) {
      delete list[i];
    }
  }

  static Move* fetch(const Move& m) { return Move::list[m.index]; }

  bool isPass() { return pass; }

  bool compare(int i, int j) { return x == i && y == j; }

  bool hasSide(uint8_t side) {
    switch (side) {
      case TOP:
        return y != 0;
      case BOT:
        return y != maxMoveSize - 1;
      case RIGHT:
        return x != maxMoveSize - 1;
      case LEFT:
        return x != 0;
    }
    return false;
  }

  // only called after hasSide for that side
  Move* getSide(uint8_t side) {
    if (hasSide(side)) {
      switch (side) {
        case TOP:
          return Move::list[index - 1];
        case BOT:
          return Move::list[index + 1];
        case RIGHT:
          return Move::list[index + maxMoveSize];
        case LEFT:
          return Move::list[index - maxMoveSize];
      }
    }
    return nullptr;
  }

  friend std::ostream& operator<<(std::ostream& os, const Move& m);
  friend std::istream& operator>>(std::istream& os, Move& m);
  friend bool operator==(const Move& cM1, const Move& cM2);
};
#endif
