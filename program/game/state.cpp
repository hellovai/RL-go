// Copyright 2014 hellovai

#include <algorithm>
#include <queue>
#include "state.h"

uint8_t nextPlayer(uint8_t player) {
  if (player == PLAYER_ONE) {
    return PLAYER_TWO;
  }
  return PLAYER_ONE;
}

State::State() {
  player = PLAYER_ONE;
  move = nullptr;
  turn = 0;

  prev = nullptr;
  next = nullptr;
  validMoves.resize(Move::maxMoveSize * Move::maxMoveSize + 1);
  validMoves.set();
  board = new uint8_t* [State::boardSize];
  for (uint8_t i = 0; i < State::boardSize; ++i) {
    board[i] = new uint8_t[State::boardSize];
  }
}

// return false if the move is invalid
// return true if valid move, then create new board as well
bool State::makeMove(Move* pos) {
  // assert liberty is still available
  int liberty_count = liberty(pos);
  if (liberty_count == 0) {
    return false;
  }

  // assert previous move won't lead to previous postion
  // TODO(hellovai): this is probably inefficient
  State* prevptr = prev;
  while (prevptr) {
    if (prevptr->move == pos)
      if (validMoves == prevptr->validMoves)
        if (memcmp(board, prevptr->board,
                   sizeof(uint8_t) * (State::boardSize)*(State::boardSize))) {
          // LOG(INFO) << "Move " << pos << " results in previous board condition";
          return false;
        }
    prevptr = prevptr->prev;
  }

  // passed all tests
  // create next board
  createNext(pos);
  return true;
}

// private functions
void State::setPosition(Move* pos) {
  board[pos->x][pos->y] = player;
  validMoves.reset(pos->index);
}

void State::unsetPosition(Move* pos) {
  board[pos->x][pos->y] = 0;
  validMoves.set(pos->index);
}

// only call after asserting that pos is a valid move to make
void State::createNext(Move* pos) {
  if (!next) {
    next = new State();
    next->prev = this;
  }
  std::copy(&board[0][0], &board[Move::maxMoveSize][Move::maxMoveSize],
            &(next->board[0][0]));
  next->player = nextPlayer(player);
  next->move = pos;
  next->setPosition(pos);
  for (int side = 0; side < NUM_SIDES; ++side) {
    if (pos->hasSide(side)) {
      Move* check = pos->getSide(side);
      if (next->liberty(check, OTHER) == 0) {
        next->eat(check);
      }
      delete check;
    }
  }
}

// returns number of liberties if you were to make a move
// TODO(hellova): find a way to store and udpate liberties to avoid
// redundant calculations
//   thoughts: store liberties with every board position
//             set empty peices which are liberties with a flag, only do updates
//                if you make a move which affects pieces which are liberties
int State::liberty(Move* toCheck, uint8_t type) {
  // set postion
  bool manualSet = false;
  if (isEmpty(toCheck)) {
    setPosition(toCheck);
    manualSet = true;
  }

  // count liberties
  std::queue<Move*> q;
  q.push(toCheck);
  int liberty = 0;

  boost::dynamic_bitset<> checkSet;
  checkSet.resize(validMoves.size());
  while (!q.empty()) {
    Move* check = q.front();
    q.pop();

    // queue all 4 sides if the current peice
    if (checkPosition(check) == type && !checkSet.test(check->index)) {
      for (int side = TOP; side < NUM_SIDES; ++side)
        if (check->hasSide(side)) {
          q.push(check->getSide(side));
        } else {
          liberty++;
        }
    }
    checkSet.set(check->index);
    if (check != toCheck) {
      delete check;
    }
  }

  // unself postion
  if (manualSet) {
    unsetPosition(toCheck);
  }
  return liberty;
}

// eat all peices which are in the pos group
void State::eat(Move* pos) {
  std::queue<Move*> q;
  q.push(pos);
  while (!q.empty()) {
    Move* check = q.front();
    q.pop();

    // queue all 4 sides if the current peice
    if (checkPosition(check) == OTHER) {
      unsetPosition(check);
      for (int side = TOP; side < NUM_SIDES; ++side)
        if (check->hasSide(side)) {
          q.push(check->getSide(side));
        }
    }
  }
}


std::ostream& operator<<(std::ostream& os, State const& b) {
  // print board
  os << "  ";
  for (int i = 0; i < State::boardSize; ++i) {
    os << " " << static_cast<char>(i + 0x41);
  }
  os << std::endl;

  for (int i = 0; i < State::boardSize; ++i) {
    os << std::setw(2) << (i + 1) << " ";
    for (int j = 0; j < State::boardSize; ++j) {
      if (b.move)
        if (b.move->compare(i, j)) {
          os << "\033[32m";
        }

      switch (b.board[i][j]) {
        case PLAYER_ONE:
          os << "\u25D8";
          break;
        case PLAYER_TWO:
          os << "\u2022";
          break;
        default:
          os << ".";
          break;
      }

      if (b.move)
        if (b.move->compare(i, j)) {
          os << "\033[0m";
        }

      os << " ";
    }
    os << " " << (i + 1) << std::endl;
  }
  os << "  ";
  for (int i = 0; i < State::boardSize; ++i) {
    os << " " << static_cast<char>(i + 0x41);
  }
  os << std::endl;
  // TODO(hellovai): print stats
  return os;
}
