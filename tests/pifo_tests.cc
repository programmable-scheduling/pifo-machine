#include <queue>
#include <iostream>
#include "gtest/gtest.h"

TEST(OmnetTests, Pifo) {
  std::priority_queue<int> q;

  for(const auto & n : {1,8,5,6,3,4,0,9,3,2})
    q.push(n);

  // Pop out and check for correctness
  std::vector<int> expected = {9, 8, 6, 5, 4, 3, 3, 2, 1, 0};
  long unsigned int count = 0;
  while(! q.empty()) {
    EXPECT_EQ(expected.at(count), q.top());
    q.pop();
    count++;
  }
}
