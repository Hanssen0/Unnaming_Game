#ifndef SRC_CPP_H_
#define SRC_CPP_H_
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
  inline void set_seed_of_random(int a) {seed_of_random_ = a;}
  inline int RandomIn(int start, int end) {
    if (start > end) std::swap(start, end);
    if (end - start > RAND_MAX) return -1;
    return (rand_r(&seed_of_random_) % (end - start + 1)) + start;
  }
 private:
  unsigned int seed_of_random_;
};
#endif  // SRC_CPP_H_
