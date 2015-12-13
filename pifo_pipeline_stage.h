#ifndef PIFO_PIPELINE_STAGE_H_
#define PIFO_PIPELINE_STAGE_H_

#include <cstdint>

/// PIFOPipelineStage models a stage of PIFOs
/// ---each of which can be a priority queue or a
/// calendar queue. The constraint that on any
/// tick you can do at most one enqueue or one dequeue
/// to the PIFOPipelineStage using the enq and deq methods.
/// These enq and deq methods can be external or from
/// previous or succeeding PIFOPipelineStage's. This mechanism
/// of muxing the various sources into a port for each PIFOPipelineStage
/// is the interconnect.

/// Also, I am not sure whether we permit fully generic PIFOs in each
/// PipelineStage, because the hardware has no understanding of these aspects.
/// In other words, types are a purely imaginary software construction.
/// The configuration of these muxes is handled by the compiler based on
/// the graphviz dot file input describing the scheduling hierarchy.
/// 3 sources of input for each pipeline stage: previous, next, and external.
/// At most one can be active at any instant and these
/// are setup well in advance in accordance with the scheduling policy.
class PIFOPipelineStage {
 public:
  /// Enqueue
  /// These happen externally
  /// and are specified by the graph describing
  /// the scheduling algorithm.
  void enq(const uint32_t & queue_id, const ElementType & element, const PriorityType & prio, const uint32_t & tick);

  /// Dequeues
  /// Happen implicitly starting from the root PIFO
  /// Where do you store the next queue to dequeue from during pointer chasing?
  Optional<ElementType> deq(const uint32_t & queue_id, const uint32_t & tick);

 private:
  /// Bank of priority queues
  std::vector<PriorityQueue> priority_queue_bank_ = {};

  /// Bank of calendar queues
  std::vector<CalendarQueue> calendar_queue_bank_ = {};
};

#endif  // PIFO_PIPELINE_STAGE_H_
