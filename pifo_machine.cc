#include "priority_queue.h"
#include "calendar_queue.h"

#include <iostream>
#include <random>

int main() {
  // Random priority generation
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> prio_dis(1, 5);
  std::uniform_int_distribution<uint32_t> ele_dis(1, 5);

  // Set up one PriorityQueue
  PriorityQueue<uint32_t, uint32_t> priority_queue;

  // Set up one CalendarQueue
  CalendarQueue<uint32_t, uint32_t> calendar_queue;

  // Execute simulation
  for (uint32_t i = 0; i < 10000; i++) {
    calendar_queue.enq(ele_dis(gen), prio_dis(gen), i);
    std::cout << calendar_queue << std::endl;
    auto result = calendar_queue.deq(i);
    std::cout << "Result is initialized " << result.initialized() << std::endl;
  }

//  priority_queue.print();
}
