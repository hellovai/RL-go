// Copyright 2014 (hellovai)

#include "../common.h"
#include "Brain.h"
#include <vector>

std::ostream& operator<<(std::ostream &out, Signature &s) {
  out << "Signature:\n" << s.p1All << "\n" << s.p2All << std::endl;
  return out;
}

void UCTBrain::simulate(Game* g) {
  GLOG(LOG(ERROR) << "Begin simuation";)
  std::vector<std::pair<Node*, Move*>> v;
  simTree(g, &v);
  int res = simDefault(g);
  _memory->backup(v, res);
}

void UCTBrain::simTree(Game* g, std::vector<std::pair<Node*, Move*>>* v) {
  GLOG(LOG(ERROR) << "Simulation in tree started";)
  Node* past = _memory->root();
  while (!g->isFinished()) {
    Signature s(g->getState());
    Node* remember = _memory->find(s);
    if (!remember) {
      GLOG(g->print();)
      remember = new Node(s);
      past->set(g->getState().move->index, remember);
      _memory->addNode(s.getMapKey(), remember);
      v->push_back({remember, g->getState().move});
      return;
    } else {
      GLOG(LOG(ERROR) << "we've seen this node before";)
    }
    Move* m = Move::list[remember->selectMove(_c, g->turn())];
    if (!g->makeMove(m)) {
      remember->setInvalid(m->index, g->turn());
      continue;
    }
    v->push_back({remember, g->getState().move});
    past = remember;
  }
}

int UCTBrain::simDefault(Game* g) {
  GLOG(LOG(ERROR) << "Simulation in default started";)
  while (!g->isFinished()) {
    std::vector<Move*> v;
    g->validMoves(v);
    Move* m = Move::list[_r->think(v, g)];
    g->makeMove(m);
  }
  return g->pWins(_player);
}
