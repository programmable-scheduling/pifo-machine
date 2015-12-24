#include <iostream>
#include <random>

#include "pifo_pipeline_stage.h"
#include "pifo_pipeline.h"

int main() {
  try {
    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> ele_dis(1, 5);

    // Traffic generation
    PIFOPacket test_packet;

    // Single PIFO pipeline stage consisting of
    // 1 priority and queue
    // (every PIFO pipeline stage has 1 calendar queue)
    PIFOPipeline pipeline({PIFOPipelineStage(1,
                                             "fid",
                                             {{1, {Operation::TRANSMIT, {}}},
                                              {2, {Operation::TRANSMIT, {}}},
                                              {3, {Operation::TRANSMIT, {}}},
                                              {4, {Operation::TRANSMIT, {}}},
                                              {5, {Operation::TRANSMIT, {}}},
                                             },
                                             [] (const auto & x) { return x("fid"); })});

    // Execute simulation
    for (uint32_t i = 0; i < 10000; i++) {
      test_packet("fid") = ele_dis(gen);
      test_packet("ptr") = 666;
      pipeline.enq(0, QueueType::PRIORITY_QUEUE, 0, test_packet, i);
    }

    std::cout << "Finished enqs\n";

    for (uint32_t i = 10000; i < 20000; i++) {
      auto result = pipeline.deq(0, QueueType::PRIORITY_QUEUE, 0, i);
      std::cout << "Deq result is \"" << result << "\"" << std::endl;
    }

    assert_exception(pipeline.deq(0, QueueType::PRIORITY_QUEUE, 0, 20000).initialized() == false);
  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
