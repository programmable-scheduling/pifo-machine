#include "priority_queue.h"

#include <iostream>
#include <random>

int main() {
  // Random priority generation
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> prio_dis(1, 10000);

  // Set up one PriorityQueue
  PriorityQueue<int> priority_queue;

  // Execute simulation
  for (uint32_t i = 0; i < 10000; i++) {
    priority_queue.enq(prio_dis(gen));
  }

  priority_queue.print();
}
