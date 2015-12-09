#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "pifo.h"

template <typename ElementType>
class PriorityQueue {
 public:
  /// Enqueue method
  void enq(const ElementType & element) { pifo_.push(element); }

  /// Dequeue method
  ElementType deq(const uint32_t & tick __attribute__((unused))) { pifo_.pop(); }

  /// Print method
  void print () const { pifo_.print_queue(); }

 private:
  /// Underlying PIFO
  PIFO<ElementType> pifo_ = {};
};

#endif  // PRIORITY_QUEUE_H_
