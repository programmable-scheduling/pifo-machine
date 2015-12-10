#ifndef PIFO_H_
#define PIFO_H_

#include <ostream>
#include <iostream>
#include <queue>

#include "optional.h"

/// Helper class for an element that can be "pushed"
/// into a PIFO i.e. a class that pairs an ElementType element
/// with a priority for that element in the PIFO
template <typename ElementType, typename PriorityType>
struct PushableElement {
 public:
  /// Print method
  friend std::ostream & operator<<(std::ostream & out, const PushableElement & push_element) {
    out << "(ele: " << push_element.element_ << ", prio: " << push_element.prio_ << ")";
    return out;
  }

  /// Override the less-than operator for std::priority_queue to work
  bool operator<(const PushableElement<ElementType, PriorityType> & other) const { return prio_ < other.prio_; }

  /// Element itself
  ElementType element_;

  /// Element's priority in PIFO
  PriorityType prio_;
};

// TODO: Put in a static assert for PriorityType
template <typename ElementType, typename PriorityType>
class PIFO {
 public:
  /// Default constructor
  PIFO() : queue_(std::priority_queue<PushableElement<ElementType, PriorityType>>()) {}

  /// Push element of ElementType into PIFO
  void push(const ElementType & element, const PriorityType & prio) {
    PushableElement<ElementType, PriorityType> element_with_prio;
    element_with_prio.element_ = element;
    element_with_prio.prio_    = prio;
    queue_.push(element_with_prio);
  }

  /// Pop and return element from the top of the PIFO
  Optional<ElementType> pop(void) {
    if (not queue_.empty()) {
      auto top_element = queue_.top();
      queue_.pop();
      return Optional<ElementType>(top_element.element_);
    } else {
      return Optional<ElementType>();
    }
  }

  /// Get element from the top of the PIFO, but don't pop it
  Optional<ElementType> top(void) const {
    if (not queue_.empty()) {
      return Optional<ElementType>(queue_.top().element_);
    } else {
      return Optional<ElementType>();
    }
  }

  /// print queue contents
  friend std::ostream & operator<<(std::ostream & out, const PIFO & pifo) {
    // Copy priority_queue and then iterate over it
    auto shadow_copy = pifo.queue_;
    while (not shadow_copy.empty()) {
      out << shadow_copy.top() << std::endl;
      shadow_copy.pop();
    }
    out << std::endl;
    return out;
  }

 private:
  /// Underlying sorted array of ElementType aka. priority_queue
  std::priority_queue<PushableElement<ElementType, PriorityType>> queue_; //std::priority_queue<PushableElement<ElementType, PriorityType>>();
};

#endif  // PIFO_H_
