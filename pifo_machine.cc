#include "priority_queue.h"
#include "calendar_queue.h"

#include <iostream>
#include <random>

int main() {
  // Random priority generation
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> prio_dis(1, 10000);

  // Set up one PriorityQueue
  PriorityQueue<uint32_t> priority_queue;

  // Set up one CalendarQueue
  CalendarQueue<uint32_t> calendar_queue;

  // Execute simulation
  for (uint32_t i = 0; i < 10000; i++) {
    priority_queue.enq(prio_dis(gen));
    calendar_queue.enq(prio_dis(gen));
    priority_queue.deq(i);
    calendar_queue.deq(i);
  }

  priority_queue.print();
  calendar_queue.print();
}
