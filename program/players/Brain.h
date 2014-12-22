#include <vector>

class Brain {
 public:
  Brain() {}
  virtual ~Brain() {}
  virtual int think(const std::vector<Move*>& v, Game* g) = 0;
};

class RandomBrain : public Brain {
 public:
  int think(const std::vector<Move*>& v, Game* g) { return rand() % v.size(); }
};
