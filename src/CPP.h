#ifndef UNNAMING_GAME_SRC_CPP_H_
#define UNNAMING_GAME_SRC_CPP_H_
#include <iostream>
#include <utility>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <queue>
#include <stack>
#include <climits>
class RandomGenerater {
 public:
  inline void set_seed_of_random(uint32_t a) {seed_of_random_ = a % UINT_MAX;}
  inline uint32_t RandomIn(uint32_t start, uint32_t end) {
    if (start > end) std::swap(start, end);
    if (end - start > RAND_MAX) return UINT32_MAX;
    return (rand_r(&seed_of_random_) % (end - start + 1)) + start;
  }
 private:
  unsigned int seed_of_random_;
};
#endif  // UNNAMING_GAME_SRC_CPP_H_
