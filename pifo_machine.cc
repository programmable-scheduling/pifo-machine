#include <iostream>
#include <random>

#include "pifo_pipeline_stage.h"

int main() {
  try {
    // Random priority generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> ele_dis(1, 5);

    // Single PIFO pipeline stage consisting of
    // 1 priority and 0 calendar queues
    typedef PIFOPipelineStage<uint32_t, uint32_t> StageType;
    StageType pipeline_stage(1, 0, {}, [] (const auto & x) { return x; });

    // Execute simulation
    for (uint32_t i = 0; i < 10000; i++) {
      pipeline_stage.enq(QueueType::PRIORITY_QUEUE, 0, ele_dis(gen), i);
      auto result = pipeline_stage.deq(QueueType::PRIORITY_QUEUE, 0, i);
      std::cout << "Result is " << result << std::endl;
      std::cout << "Pipeline stage contents " << pipeline_stage << std::endl;
    }

  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
