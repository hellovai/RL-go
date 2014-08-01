// Copyright 2014 hellovai

#include "game.h"

Game::Game() {
  debug = false;
  finished = false;
  startState = new State();
  currState = startState;
}

void Game::reset() {
  while (currState != startState) {
    currState = currState->prev;
    delete currState->next;
  }
  currState = startState;
  finished = false;
}

boost::dynamic_bitset<> Game::validMoves() {
  return currState->validMoves;
}

bool Game::makeMove(Move* move) {
  if (currState->makeMove(move)) {
    if (move->isPass() && currState->pass) {
      finished = true;
    }
    currState = currState->next;
    return true;
  } else {
    LOG(ERROR) << "Invalid Move: " << *move;
    return false;
  }
}

void Game::undo() {
  if (currState->prev) {
    currState = currState->prev;
  } else {
    // LOG(INFO) << "Undo not available";
  }
}

void Game::redo() {
  if (currState->next) {
    currState = currState->next;
  } else {
    // LOG(INFO) << "Redo not available";
  }
}
