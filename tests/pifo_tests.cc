#include <queue>
#include <iostream>
#include "gtest/gtest.h"

template <typename T>
bool check_for_correctness(std::priority_queue<T> & q) {
  auto last_element = q.top();
  while(! q.empty()) {
    // Every top element must be <= the previous one
    EXPECT_LE(q.top(), last_element);
    q.pop();
  }
  assert(q.empty());
  return true;
}

TEST(PifoTests, Pifo) {
  // Push packets into priority queue
  std::priority_queue<int> q;
  for(const auto & n : {1,8,5,6,3,4,0,9,3,2})
    q.push(n);

  check_for_correctness(q);

  for(const auto & n : {1,1,50,60,-3,4,-1,9,-30,2})
    q.push(n);

  check_for_correctness(q);
}
