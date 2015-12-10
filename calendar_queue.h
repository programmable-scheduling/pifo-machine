#ifndef CALENDAR_QUEUE_H_
#define CALENDAR_QUEUE_H_

#include <iostream>

#include "pifo.h"

/// Calendar queue abstraction to determine
/// time of transmission of packets
template <typename ElementType, typename PriorityType>
class CalendarQueue {
 public:
  /// Enqueue method
  /// TODO: I think we should supply both an element and a priority/departure time
  /// For now, we assume the element has the priority as well.
  void enq(const ElementType & element, const PriorityType & prio, const uint32_t & tick) {
    // Don't push in a packet that was due in the past.
    assert_exception(prio >= tick);
    pifo_.push(element, prio);
  }

  /// Dequeue method
  Optional<ElementType> deq(const uint32_t & tick) {
    // Get top of pifo
    auto top = pifo_.top();

    if (top.initialized() and top.get() >= tick) {
      // Make sure the top element and the current time match up
      assert_exception(top.get() == tick);
      return pifo_.pop();
    } else {
      std::cout << "Returning nothing \n";
      return Optional<ElementType>();
    }
  }

  /// Print method
  friend std::ostream & operator<<(std::ostream & out, const CalendarQueue & calendar_queue) {
    out << calendar_queue.pifo_ << std::endl;
    return out;
  }

 private:
  /// Underlying PIFO
  PIFO<ElementType, PriorityType> pifo_ = {};
};

#endif  // CALENDAR_QUEUE_H_
