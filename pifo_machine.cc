#include <iostream>
#include <random>

#include "pifo_pipeline_stage.h"
#include "pifo_pipeline.h"

struct Packet {
  /// Fields
  int fid = 0;

  /// Stream insertion operator to print PIFO contents when it contains a Packet
  friend std::ostream & operator<<(std::ostream & out, const Packet & packet) {
    out << packet.fid;
    return out;
  }

  /// Override less-than operator because Packet needs to be part of a std::map
  bool operator<(const Packet & other) const { return fid < other.fid; }
};

int main() {
  try {
    // Random priority generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> ele_dis(1, 5);

    // Single PIFO pipeline stage consisting of
    // 1 priority and 0 calendar queues
    typedef PIFOPipelineStage<Packet, uint32_t> StageType;
    typedef PIFOPipeline<Packet, uint32_t> PipelineType;
    PipelineType pipeline({StageType(1, 0, {{Packet(), {Operation::TRANSMIT, 0, QueueType::PRIORITY_QUEUE, 0}}}, [] (const auto & x) { return x.fid; })});

    // Execute simulation
    for (uint32_t i = 0; i < 10000; i++) {
      pipeline.enq(0, QueueType::PRIORITY_QUEUE, 0, Packet(), i);
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
