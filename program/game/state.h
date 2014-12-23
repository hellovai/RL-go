// Copyright 2014 hellovai

#ifndef __STATE_H_INCLUDED__
#define __STATE_H_INCLUDED__
#include "../common.h"

#include <boost/dynamic_bitset.hpp>
#include "move.h"

typedef enum {
  SELF = 0,
  OTHER = 3,
} CheckType;

uint8_t nextPlayer(uint8_t player);

class State {
 public:
  static int boardSize;
  // this defines the player who's turn it is, and the most recent move made
  uint8_t player;
  Move* move;
  bool pass;
  uint8_t** board;

  boost::dynamic_bitset<> validMoves;
  State* prev;
  State* next;

  State();
  ~State() {
    for (int i = 0; i < boardSize; ++i) {
      delete[] board[i];
    }
    delete[] board;

    if (next) {
      next->prev = nullptr;
      delete next;
    }

    if (prev) {
      prev->next = nullptr;
      delete prev;
    }
  }

  bool makeMove(Move* pos);

  friend std::ostream& operator<<(std::ostream& os, const State& b);

  // copy
  State* clone() {
    State* s = new State();
    s->player = player;
    s->move = move;
    s->pass = pass;
    s->validMoves = validMoves;
    for (int i = 0; i < State::boardSize; i++)
      for (int j = 0; j < State::boardSize; j++)
        s->board[i][j] = board[i][j];

    return s;
  }

 private:
  // checks if the position is owned by current player, empty, or opponent
  uint8_t checkPosition(Move* pos) { return board[pos->x][pos->y] ^ player; }
  bool isEmpty(Move* pos) { return validMoves.test(pos->index); }

  void setPosition(Move* pos);
  void unsetPosition(Move* pos);
  void createNext(Move* pos);
  int liberty(Move* pos, uint8_t type = SELF);
  void eat(Move* pos);
};

#endif
