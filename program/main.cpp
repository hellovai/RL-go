// Copyright 2014 (hellovai)

#include "common.h"

#include <iostream>
#include "game/game.h"
#include "players/Player.h"
#include "players/AIPlayer.h"
#include "GameContainer.h"

GFLAGS(DEFINE_int32(boardsize, 19, "modify boardsize of the game");
       , int FLAGS_boardsize = 19;)

int State::boardSize = FLAGS_boardsize;
int Move::maxMoveSize = FLAGS_boardsize;
int Node::maxActions = FLAGS_boardsize * FLAGS_boardsize + 1;

int main(int argc, char* argv[]) {
  GLOG(google::InitGoogleLogging(argv[0]);)

  srand(time(NULL));

  Move::fill(0, Move::maxMoveSize * Move::maxMoveSize + 1);
  Game* game = new Game();
  Player* p1 = new UCTAIPlayer(game, "Player 1");
  Player* p2 = new RandomAIPlayer(game, "Player 2");

  GameContainer c(game, p1, p2);
  c.start(1);

  delete p1;
  delete p2;
  delete game;
  Move::unfill();

  GLOG(google::ShutDownCommandLineFlags();)
  return 0;
}

float frand(float m, bool sign) {
  return sign ? ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                  2 * m) -
                 m)
              : (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * m);
}
