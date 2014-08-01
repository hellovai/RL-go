// Copyright 2014 hellovai

#ifndef __STATE_H_INCLUDED__
#define __STATE_H_INCLUDED__

#include <boost/dynamic_bitset.hpp>

#include <glog/logging.h>
#include "move.h"

#define PLAYER_ONE 1
#define PLAYER_TWO 2

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
  int turn;
  uint8_t** board;

  boost::dynamic_bitset<> validMoves;
  State* prev;
  State* next;

  explicit State();
  ~State() {}

  bool makeMove(Move* pos);
  friend std::ostream& operator<<(std::ostream& os, const State& b);

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
