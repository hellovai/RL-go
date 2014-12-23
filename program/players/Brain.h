// Copyright 2014 (hellovai)

#include <vector>
#include <time.h>
#include "../game/game.h"
#include "Signature.h"
#include "Tree.h"

class Brain {
 public:
  Brain() {}
  virtual ~Brain() {}
  virtual int think(const std::vector<Move*>& v, Game* g) = 0;
};

class RandomBrain : public Brain {
 public:
  int think(const std::vector<Move*>& v, Game* g) {
    int i = rand() % v.size();
    return v[i]->index;
  }
};

class UCTBrain : public Brain {
  Tree* _memory;
  RandomBrain* _r;
  float _c;     // exploration constant
  int _player;  // this is iteration specific so do not refer to this ever

  void simulate(Game* g);
  void simTree(Game* g, std::vector<std::pair<Node*, Move*>>* v);
  int simDefault(Game* g);

 public:
  explicit UCTBrain(float c = 1.0) : Brain(), _c(c) {
    _r = new RandomBrain();
    _memory = new Tree();
  }
  ~UCTBrain() { delete _memory; delete _r; }

  int think(const std::vector<Move*>& v, Game* g) {
    GLOG(LOG(ERROR) << "Starting to think";)
    Game* g2 = new Game();
    g2->clone(g);
    _player = g2->turn();
    time_t timer = time(NULL);
    while (difftime(time(NULL), timer) < 0.5) {
      GLOG(LOG(ERROR) << "Simution " << i << " started";)
      simulate(g2);
      g2->setStartState();
      GLOG(LOG(ERROR) << "Simution " << i << " complete";)
    }
    delete g2;
    GLOG(LOG(ERROR) << "testing delete";)
    Signature s(g->getState());
    Node* n = _memory->find(s);
    GLOG(CHECK_NOTNULL(n));
    int index = n->selectMove(0, g->turn());
    return index;
  }
};
