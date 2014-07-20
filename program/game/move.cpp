// Copyright 2014 hellovai

#include "move.h"

std::ostream& operator<<(std::ostream &os, Move const& m) {
  return m.pass ? os << "PASS" : os << static_cast<char>(m.x + 0x41) << m.y + 1;
}

std::istream& operator>>(std::istream &input, Move & m) {
  char x;
  int y;
  input >> x;
  if (x == 'p' || x == 'P') {
    m.pass = true;
  } else {
    input >> y;
    m.x = static_cast<int>(x) - 0x41;
    m.y = y;
    m.pass = false;
    m.setIndex();
  }
  return input;
}

