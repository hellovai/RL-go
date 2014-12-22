// Copyright 2014 hellovai

#include "game.h"

Game::Game() {
  debug = false;
  finished = false;
  startState = new State();
  currState = startState;
  _turn = 1;
}

void Game::reset() {
  while (currState != startState) {
    currState = currState->prev;
    delete currState->next;
  }
  currState = startState;
  finished = false;
  _turn = 1;
}

void Game::validMoves(std::vector<Move*>& v) const {
  int idx = currState->validMoves.find_first();
  while (idx != boost::dynamic_bitset<>::npos) {
    v.push_back(Move::list[idx]);
    idx = currState->validMoves.find_next(idx);
  }
}

bool Game::makeMove(Move* move) {
  if (currState->makeMove(move)) {
    if (move->isPass() && currState->pass) {
      finished = true;
    }
    currState = currState->next;
    _turn++;
  } else {
    GLOG(LOG(ERROR) << "Invalid Move: " << *move;)
    return false;
  }
  return true;
}

void Game::undo() {
  if (currState->prev) {
    currState = currState->prev;
    _turn--;
  } else {
    GLOG(LOG(ERROR) << "Undo not available";)
  }
}

void Game::redo() {
  if (currState->next) {
    currState = currState->next;
    _turn++;
  } else {
    GLOG(LOG(ERROR) << "Redo not available";)
  }
}
