#include <iostream>
#include <random>

#include "priority_queue.h"
#include "calendar_queue.h"
#include "pifo_pipeline_stage.h"

int main() {
  try {
    // Random priority generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> prio_dis(1, 5);
    std::uniform_int_distribution<uint32_t> ele_dis(1, 5);

    // Single PIFO pipeline stage consisting of
    // 10 priority and 10 calendar queues
    PIFOPipelineStage<uint32_t, uint32_t> pipeline_stage(10, 10);

    // Set up one PriorityQueue
    PriorityQueue<uint32_t, uint32_t> priority_queue;

    // Set up one CalendarQueue
    CalendarQueue<uint32_t, uint32_t> calendar_queue;

    // Execute simulation
    for (uint32_t i = 0; i < 10000; i++) {
      priority_queue.enq(ele_dis(gen), prio_dis(gen), i);
      std::cout << priority_queue << std::endl;
      auto result = priority_queue.deq(i);
      std::cout << "Result is initialized " << result.initialized() << std::endl;
    }

  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
