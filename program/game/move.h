// Copyright 2014 hellovai

#ifndef __MOVE_H_INCLUDED__
#define __MOVE_H_INCLUDED__

#include <stdint.h>
#include <iostream>
#include <iomanip>

typedef enum {
  TOP,
  BOT,
  RIGHT,
  LEFT,
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
      index = pass ? maxMoveSize * maxMoveSize + 1
      : x * maxMoveSize + y;
    }
    explicit Move(Move* curr)
    : x(curr->x), y(curr->y), pass(curr->pass), index(curr->index) {}
    Move(int x_, int y_) : x(x_), y(y_) {
      pass = x < 0 || y < 0;
      index = pass ? maxMoveSize * maxMoveSize + 1
      : x * maxMoveSize + y;
    }
    explicit Move(int i) : index(i) {
      x = index / maxMoveSize;
      y = index % maxMoveSize;
      pass = index == maxMoveSize * maxMoveSize + 1;
    }
    ~Move() {}

    void setIndex() {
      index = pass ? maxMoveSize * maxMoveSize + 1
      : x * maxMoveSize + y;
    }

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
      return true;
    }

    // TODO(hellovai): add asserts
    // only called after hasSide for that side
    Move* getSide(uint8_t side) {
      Move* next = new Move(this);
      switch (side) {
        case TOP:
        next->y--;
        next->index--;
        case BOT:
        next->y++;
        next->index++;
        case RIGHT:
        next->x++;
        next->index += maxMoveSize;
        case LEFT:
        next->x--;
        next->index -= maxMoveSize;
      }
      return next;
    }

    friend std::ostream& operator<<(std::ostream& os, const Move& m);
    friend std::ostream& operator>>(std::ostream& os, const Move& m);
};
#endif
