#ifndef PIFO_PIPELINE_H_
#define PIFO_PIPELINE_H_

#include "pifo_pipeline_stage.h"

/// A pipeline of PIFOStages
/// Used (for instance) for hierarchical scheduling
class PIFOPipeline {
 public:
  /// Constructor for the PIFOPipeline from an std::initializer_list
  PIFOPipeline(const std::initializer_list<PIFOPipelineStage> & t_pipeline_stages)
      : PIFOPipeline(std::vector<PIFOPipelineStage>(t_pipeline_stages)) {}

  /// Constructor for the PIFOPipeline from vector
  PIFOPipeline(const std::vector<PIFOPipelineStage> & t_stages)
      : stages_(t_stages) {}

  /// Enqueue into the pipeline at every tick
  /// Returns nothing because the packet is just assumed to be pushed in
  /// If we need to enqueue into multiple prio / cal qs, we need to call enq
  /// multiple times.
  void enq(const uint32_t & stage_id,
           const QueueType & q_type,
           const uint32_t & queue_id,
           const PIFOPacket & packet,
           const uint32_t & tick) {
    stages_.at(stage_id).enq(q_type, queue_id, packet, tick);
  }

  /// Dequeues from the pipeline at every tick
  /// Dequeue recursively until we either find a packet
  /// or we push an output from a calendar queue into the next stage
  Optional<PIFOPacket> deq(const uint32_t & stage_id,
                           const QueueType & q_type,
                           const uint32_t & queue_id,
                           const uint32_t & tick) {
    // Start off with a dequeue operation to the specified stage_id
    NextHop next_hop = {Operation::DEQ, stage_id, q_type, queue_id};

    // Keep dequeuing until the next operation is either
    // an Operation::ENQ (push from prio q.) or
    // an Operation::TRANSMIT (reached a packet, transmit it)
    Optional<PIFOPacket> ret;
    while (next_hop.op == Operation::DEQ) {
      ret = stages_.at(next_hop.stage_id).deq(next_hop.q_type, next_hop.queue_id, tick);
      // Check that ret is initialized.
      if (ret.initialized()) {
        next_hop = stages_.at(next_hop.stage_id).find_next_hop(ret.get());
      } else {
        return ret;
      }
    }

    // Handle loop termination appropriately
    assert_exception(ret.initialized());
    if (next_hop.op == Operation::ENQ) {
      // This only happens if a calendar queue pushes into the next stage
      stages_.at(next_hop.stage_id).enq(next_hop.q_type,
                                        next_hop.queue_id,
                                        ret.get(),
                                        tick);
      return Optional<PIFOPacket>();
    } else {
      // This is when we have finally reached a packet, which needs to
      // be pulled out of the data buffer and transmitted on the link.
      assert_exception(next_hop.op == Operation::TRANSMIT);
      return ret;
    }
  }

  /// Overload stream insertion operator
  friend std::ostream & operator<<(std::ostream & out, const PIFOPipeline & t_pipeline) {
    out << "Contents of PIFOPipeline " << std::endl;
    for (uint32_t i = 0; i < t_pipeline.stages_.size(); i++) {
      out << "Stage " << i << " " << t_pipeline.stages_.at(i);
    }
    return out;
  }

 private:
  /// Bank of pipeline stages
  std::vector<PIFOPipelineStage> stages_        = {};
};

#endif  // PIFO_PIPELINE_H_
