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

std::vector<Move> Game::validMoves() {
  std::vector<Move> v(currState->validMoves.count());
  int idx = currState->validMoves.find_first();
  int i = 0;
  while (idx != boost::dynamic_bitset<>::npos) {
    v[i++].reset(idx);
    idx = currState->validMoves.find_next(idx);
  }
  return v;
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
    delete move;
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
