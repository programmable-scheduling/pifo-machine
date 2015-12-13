#ifndef ABSTRACT_QUEUE_H_
#define ABSTRACT_QUEUE_H_

#include "optional.h"
/// Abstract base class for both PriorityQueue
/// and CalendarQueue, to provide queue-like interface
/// (enqueue and dequeue virtual methods)
/// This is useful when we need to instantiate a bank
/// of abstactqueues without committing to which is which
/// at the hardware level.
template <typename ElementType, typename PriorityType>
class AbstractQueue {
 public:
  /// Enqueue method
  virtual void enq(const ElementType & element, const PriorityType & prio, const uint32_t & tick) = 0;

  /// Dequeue method
  virtual Optional<ElementType> deq(const uint32_t & tick) = 0;

  /// Virtual dtor to shut up g++-4.9
  virtual ~AbstractQueue() {}
};

#endif  // ABSTRACT_QUEUE_H_
