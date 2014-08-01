// Copyright 2014 hellovai

#ifndef __MOVE_H_INCLUDED__
#define __MOVE_H_INCLUDED__

#include <stdint.h>
#include <iostream>
#include <iomanip>

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
    int x;
    int y;
    bool pass;

    int index;

  public:
    Move() : pass(true), x(-1), y(-1) {
      index = pass ? maxMoveSize * maxMoveSize
      : x * maxMoveSize + y;
    }
    explicit Move(Move* curr)
    : x(curr->x), y(curr->y), pass(curr->pass), index(curr->index) {}
    Move(int x_, int y_) : x(x_), y(y_) {
      pass = x < 0 || y < 0;
      index = pass ? maxMoveSize * maxMoveSize
      : x * maxMoveSize + y;
    }
    explicit Move(int i) : index(i) {
      x = index / maxMoveSize;
      y = index % maxMoveSize;
      pass = index == maxMoveSize * maxMoveSize;
    }
    ~Move() {}

    void setIndex() {
      index = pass ? maxMoveSize * maxMoveSize
      : x * maxMoveSize + y;
    }

    bool isPass() { return pass; }

    bool compare(int i, int j) { return x == i && y == j; }
    bool hasSide(uint8_t side) {
      switch (side) {
        case TOP:
        return y != 0;
        case BOT:
        return y != maxMoveSize;
        case RIGHT:
        return x != maxMoveSize;
        case LEFT:
        return x != 0;
      }
      return false;
    }

    // TODO(hellovai): add asserts
    // only called after hasSide for that side
    Move* getSide(uint8_t side) {
      Move* next = new Move(this);
      switch (side) {
        case TOP:
          next->y--;
          break;
        case BOT:
          next->y++;
          break;
        case RIGHT:
          next->x++;
          break;
        case LEFT:
          next->x--;
          break;
      }
      next->setIndex();
      return next;
    }

    friend std::ostream& operator<<(std::ostream& os, const Move& m);
    friend std::ostream& operator>>(std::ostream& os, const Move& m);
    friend bool operator== (const Move &cM1, const Move &cM2);
};
#endif
