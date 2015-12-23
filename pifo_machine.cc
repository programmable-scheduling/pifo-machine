#include <iostream>
#include <random>

#include "pifo_pipeline_stage.h"
#include "pifo_pipeline.h"

int main() {
  try {
    // Random priority generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> ele_dis(1, 5);

    // Single PIFO pipeline stage consisting of
    // 1 priority and 0 calendar queues
    PIFOPipeline pipeline({PIFOPipelineStage(1,
                                             0,
                                             "fid",
                                             {{0, {Operation::TRANSMIT, {{0, QueueType::PRIORITY_QUEUE, 0}}}}},
                                             [] (const auto & x) { return x("fid"); })});

    // Execute simulation
    for (uint32_t i = 0; i < 10000; i++) {
      pipeline.enq(0, QueueType::PRIORITY_QUEUE, 0, PIFOPacket(), i);
      std::cout << pipeline << std::endl;
      if (i % 5 == 0) {
        auto result = pipeline.deq(0, QueueType::PRIORITY_QUEUE, 0, i);
        std::cout << "Deq result is \"" << result << "\"" << std::endl;
      }
    }
  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
