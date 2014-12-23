// Copyright 2014 (hellovai)

#include <utility>
#include <vector>
#include <map>
#include <cmath>
#include "../common.h"
#include "Signature.h"

class Node;

typedef struct __action {
  int n;    // number of visits to each action
  float q;  // expected value of result
  Node* _res;
  __action() : n(0), q(0.0), _res(nullptr) {}
} Action;

class Node {
  Signature* _s;
  int _n;      // number of visits to node
  Action* _w;  // weights for each action data

 private:
  inline float calcuate(int index, int c, int player) {
    if (!_w[index]._res) return 0.0;
    if (_w[index]._res == this && index != maxActions - 1)
      return ((player == PLAYER_ONE) * 2 - 1) * -100000.0;
    return _w[index].q +
           ((player == PLAYER_ONE) * 2 - 1) * c *
               sqrt(log(_n) / static_cast<float>(_w[index].n));
  }

 public:
  static int maxActions;

 public:
  Node() : _n(0) {
    _s = new Signature();
    _w = new Action[maxActions];
  }
  Node(const Signature& s) : _n(0) {
    _s = new Signature(s);
    _w = new Action[maxActions];
  }
  ~Node() {
    delete _s;
    delete[] _w;
  }

  int selectMove(float c, int player) {
    float val = calcuate(0, c, player);
    int index = 0;
    for (int i = 1; i < maxActions; ++i) {
      int temp = calcuate(i, c, player);
      if (temp == val && frand() < 1.0 / (i + 1.0)) {
        val = temp;
        index = i;
      } else if ((player == PLAYER_ONE && temp > val) ||
                 (player == PLAYER_TWO && temp < val)) {
        val = temp;
        index = i;
      }
    }
    return index;
  }

  void set(int actionIndex, Node* _r) {
    GLOG(if (_w[actionIndex]._res))
    GLOG(LOG(ERROR) << "Action index exists " << actionIndex;)
    _w[actionIndex]._res = _r;
  }

  void visit() { _n++; }

  void update(int actionIndex, int result) {
    _w[actionIndex].n++;
    _w[actionIndex].q +=
        (result - _w[actionIndex].q) / static_cast<float>(_w[actionIndex].n);
  }

  void setInvalid(int actionIndex, int player) {
    _w[actionIndex]._res = this;
    _w[actionIndex].n = 1;
    _w[actionIndex].q = 100000 * (player == PLAYER_ONE ? 1 : -1);
  }

  bool operator==(const Signature& s) { return *_s == s; }
  // bool operator<(const Signature& s) { return *_s < s; }
  // bool operator!=(const Signature& s) { return !((*this) == s); }
  // bool operator<=(const Signature& s) { return ((*this) == s || (*this) < s);
  // }
  // bool operator>(const Signature& s) { return !((*this) <= s); }
  // bool operator>=(const Signature& s) { return !((*this) < s); }
};

class Tree {
  typedef std::map<MapKey, std::vector<Node*>> Recall;
  typedef std::map<MapKey, std::vector<Node*>>::iterator RecallIt;
  typedef std::map<MapKey, std::vector<Node*>>::const_iterator RecallItConst;

  Node* _root;
  Recall _access;

 public:
  Tree() {
    _root = new Node();
    addNode(static_cast<MapKey>(std::make_pair(0, 0)), _root);
  }
  ~Tree() {
    for (RecallIt it = _access.begin(); it != _access.end(); ++it) {
      for (std::vector<Node*>::iterator i = it->second.begin();
           i != it->second.end(); ++i) {
        delete *i;
      }
    }
  }

  Node* root() { return _root; }

  Node* find(const Signature& s) const {
    const MapKey m = s.getMapKey();
    RecallItConst it = _access.find(m);
    if (it == _access.end()) {
      GLOG(LOG(ERROR) << "No signature " << m.first << " " << m.second;)
      return nullptr;
    }
    const std::vector<Node*>& v = it->second;
    for (int i = 0; i < v.size(); i++) {
      if (*(v[i]) == s) {
        GLOG(LOG(INFO) << "FOUND signature";)
        return v[i];
      }
    }
    return nullptr;
  }

  void backup(const std::vector<std::pair<Node*, Move*>>& v, int result) {
    for (std::vector<std::pair<Node*, Move*>>::const_iterator i = v.begin();
         i != v.end(); ++i) {
      i->first->visit();
      i->first->update(i->second->index, result);
    }
  }

  void addNode(const MapKey& m, Node* n) {
    if (_access.find(m) == _access.end()) {
      GLOG(LOG(ERROR) << "Adding node! " << m.first << " " << m.second;)
      _access[m] = std::vector<Node*>(0);
    }
    _access[m].push_back(n);
  }
};
