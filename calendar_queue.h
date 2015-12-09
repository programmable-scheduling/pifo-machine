#ifndef CALENDAR_QUEUE_H_
#define CALENDAR_QUEUE_H_

#include <iostream>

#include "pifo.h"
#include "element_gate.h"

/// Calendar queue abstraction to determine
/// time of transmission of packets
template <typename ElementType>
class CalendarQueue {
 public:
  /// Enqueue method
  /// TODO: I think we should supply both an element and a priority/departure time
  /// For now, we assume the element has the priority as well.
  void enq(const ElementType & element) {
    if (not element_gate_.contains_packet()) {
      element_gate_.add_element(element, element);
      // TODO: This (element, element) argument list is redudnant.
      // We need to fix this to make sure we can supply an element and its
      // priority independently.
    } else {
      pifo_.push(element);
    }
  }

  /// Dequeue method
  Optional<ElementType> deq(const uint32_t & tick) {
    if (element_gate_.can_depart(tick)) {
      // Get the element from the element gate
      auto ret = element_gate_.remove_element(tick);

      // Find next element from the PIFO and move it into the element gate
      // i.e. if one exists at all
      auto next = pifo_.pop();
      if (next.initialized()) element_gate_.add_element(next.get(), next.get()); // TODO: Fix this.

      // Return.
      return ret;
    } else {
      std::cout << "Returning nothing \n";
      return Optional<ElementType>();
    }
  }

  /// Print method
  void print() const {
    std::cout << "Inside PIFO ";
    pifo_.print_queue();
    std::cout << std::endl;
    std::cout << "Inside element gate ";
    element_gate_.print();
    std::cout << std::endl;
  }

 private:
  /// Underlying PIFO
  PIFO<ElementType> pifo_ = {};

  /// Underlying element gate
  ElementGate<ElementType> element_gate_ = {};
};

#endif  // CALENDAR_QUEUE_H_
