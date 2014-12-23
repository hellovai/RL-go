// Copyright 2014 (hellovai)

#ifndef __SIGNATURE_H_INCLUDED__
#define __SIGNATURE_H_INCLUDED__

#include <utility>
#include <iostream>
#include "../game/state.h"

typedef std::pair<int, int> MapKey;

class Signature {
  boost::dynamic_bitset<> p1All;
  boost::dynamic_bitset<> p2All;

 public:
  Signature() {
    p1All.resize(State::boardSize * State::boardSize);
    p2All.resize(State::boardSize * State::boardSize);
    p1All.reset();
    p2All.reset();
  }

  explicit Signature(const State& s) {
    p1All.resize(State::boardSize * State::boardSize);
    p2All.resize(State::boardSize * State::boardSize);
    for (int i = 0; i < State::boardSize; ++i)
      for (int j = 0; j < State::boardSize; ++j)
        if (s.board[i][j] == PLAYER_ONE)
          p1All.set(i * State::boardSize + j);
        else if (s.board[i][j] == PLAYER_TWO)
          p2All.set(i * State::boardSize + j);
  }
  ~Signature() {}

  bool operator==(const Signature& other) {
    return (p1All == other.p1All && p2All == other.p2All) ||
           (p1All == other.p2All && p2All == other.p1All);
  }

  friend std::ostream& operator<<(std::ostream &out, Signature &s);

  const MapKey getMapKey() const { return {p1All.count(), p2All.count()}; }
};

#endif
