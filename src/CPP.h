#ifndef UNNAMING_CPP_H_
#define UNNAMING_CPP_H_
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <queue>
#include <stack>
inline int random_in(int start, int end) {
  if (start > end) std::swap(start, end);
  if (end - start > RAND_MAX) return -1;
  return rand() % (end - start + 1) + start;
}
#endif
