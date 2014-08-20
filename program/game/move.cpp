// Copyright 2014 hellovai

#include "move.h"

std::ostream& operator<<(std::ostream &os, Move const& m) {
  return m.pass ? os << "PASS" : os << static_cast<char>(m.y + 0x41) << m.x + 1;
}

// TODO(hellovai): why doesn't this work?
std::istream& operator>>(std::istream &input, Move & m) {
  char x;
  int y;
  input >> x;
  if (x == 'p' || x == 'P') {
    std::cout << x << std::endl;
    m.x = -1;
    m.x = -1;
    m.pass = true;
    m.setIndex();
  } else {
    input >> y;
    m.y = static_cast<int>(x) - 0x41;
    m.x = y;
    m.pass = false;
    m.setIndex();
  }
  return input;
}

bool operator==(const Move &cM1, const Move &cM2) {
  return cM1.index == cM2.index;
}
