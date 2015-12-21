#ifndef PIFO_PIPELINE_STAGE_H_
#define PIFO_PIPELINE_STAGE_H_

#include <cstdint>

#include <map>
#include <functional>

#include "priority_queue.h"
#include "calendar_queue.h"

/// enum to distinguish between priority and calendar queues
/// This lets us keep each in its own distinct namespace without
/// having to create a polymorphic queue class
enum class QueueType {
  PRIORITY_QUEUE,
  CALENDAR_QUEUE
};

/// Opcode class, specify whether we are doing
/// an enqueue / dequeue / transmit.
enum class Operation {
  ENQ,
  DEQ,
  TRANSMIT
};

/// Next hop information, what operation, which stage,
/// which queue type and which queue id should we be
/// sending this ElementType to?
struct NextHop {
  /// Operation: ENQ/DEQ/TRANSMIT
  Operation op;

  /// Which stage to enqueue or dequeue from
  uint32_t  stage_id;

  /// Queue type (calendar / prio. q) to enqueue or dequeue from
  QueueType q_type;

  /// Queue id to enqueue or dequeue from
  uint32_t  queue_id;
};

/// PIFOPipelineStage models a stage of PIFOs
/// ---each of which can be a priority queue or a calendar queue.
/// On any tick, there can be at most one enqueue and one dequeue
/// to the PIFOPipelineStage using the enq and deq methods.
/// These enq and deq methods can be external or from adjacent stages.
/// A lookup table within each stage tells each packet where to go next.
/// The compiler fills in the lut based on the graphviz dot file
/// describing the scheduling hierarchy.
template <typename ElementType, typename PriorityType>
class PIFOPipelineStage {
 public:
  typedef PushableElement<ElementType, PriorityType> PushableElementType;

  /// Constructor for PIFOPipelineStage with a number of prio. and cal. qs
  PIFOPipelineStage(const uint32_t & num_prio_queues,
                    const uint32_t & num_cal_queues)
      : priority_queue_bank_(num_prio_queues),
        calendar_queue_bank_(num_cal_queues) {}

  /// Enqueue
  /// These happen externally from the ingress pipeline
  /// or from a push from a calendar queue/
  void enq(const QueueType & q_type, const uint32_t & queue_id,
           const ElementType & element, const PriorityType & prio,
           const uint32_t & tick) {
    const auto transformed = prio_computer_(PushableElementType(element, prio));
    if (q_type == QueueType::PRIORITY_QUEUE) {
      priority_queue_bank_.at(queue_id).enq(transformed.element_,
                                            transformed.prio_, tick);
    } else {
      calendar_queue_bank_.at(queue_id).enq(transformed.element_,
                                            transformed.prio_, tick);
    }
  }

  /// Dequeues
  /// Happen implicitly starting from the root PIFO
  Optional<ElementType> deq(const QueueType & q_type, const uint32_t & queue_id,
                            const uint32_t & tick) {
    if (q_type == QueueType::PRIORITY_QUEUE) {
      return priority_queue_bank_.at(queue_id).deq(tick);
    } else {
      return calendar_queue_bank_.at(queue_id).deq(tick);
    }
  }

  /// Overload stream insertion operator
  friend std::ostream & operator<<(std::ostream & out, const PIFOPipelineStage & pipe_stage) {
    out << "Contents of PIFOPipelineStage " << std::endl;
    out << "Priority Queues: " << std::endl;
    for (uint32_t i = 0; i < pipe_stage.priority_queue_bank_.size(); i++) {
      out << "Index " << i << " " << pipe_stage.priority_queue_bank_.at(i) << std::endl;
    }

    out << "Calendar Queues: " << std::endl;
    for (uint32_t i = 0; i < pipe_stage.calendar_queue_bank_.size(); i++) {
      out << "Index " << i << " " << pipe_stage.calendar_queue_bank_.at(i) << std::endl;
    }
    out << "End of contents of PIFOPipelineStage " << std::endl;

    return out;
  }

  /// Find "next hop" after a dequeue
  NextHop find_next_hop(const ElementType & element) const { return next_hop_lut_.at(element); }

 private:
  /// Bank of priority queues
  std::vector<PriorityQueue<ElementType, PriorityType>> priority_queue_bank_ = {};

  /// Bank of calendar queues
  std::vector<CalendarQueue<ElementType, PriorityType>> calendar_queue_bank_ = {};

  /// look-up table to find the next hop
  const std::map<ElementType, NextHop> next_hop_lut_ = {};

  /// Function object to compute incoming element's priority
  /// Identity function by default
  const std::function<PushableElementType(PushableElementType)> prio_computer_ = [] (const auto & x) { return x; };
};

#endif  // PIFO_PIPELINE_STAGE_H_
