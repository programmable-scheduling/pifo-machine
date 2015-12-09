#ifndef ELEMENT_GATE_H_
#define ELEMENT_GATE_H_

#include <cassert>
#include <iostream>

/// Waiting area for a single element until it
/// is ready to depart, used for non-work-conserving
/// scheduling disciplines
template <typename ElementType>
class ElementGate {
 public:
  /// Add a single element
  void add_element(const ElementType & t_element, const uint32_t & t_dep_time) {
    assert(not contains_packet_);
    element_         = t_element;
    contains_packet_ = true;
    dep_time_        = t_dep_time;
  }

  /// Check whether there is a packet or not
  bool contains_packet(void) const { return contains_packet_; }

  /// Check whether element can depart?
  bool can_depart(const uint32_t & now) const { return now == dep_time_; }

  /// Remove element and return it, if one exists
  Optional<ElementType> remove_element(const uint32_t & now) {
    if (can_depart(now)) {
      contains_packet_ = false;
      return Optional<ElementType>(element_);
    } else {
      return Optional<ElementType>();
    }
  }

  /// Print element for debugging
  void print() const { std::cout << element_ << std::endl; }

 private:
  /// Scheduled departure time for this element
  uint32_t dep_time_    = 0;

  /// Does the ElementGate object contain an element?
  bool contains_packet_ = false;

  /// Storage area for the element
  ElementType element_ = {};
};

#endif // ELEMENT_GATE_H_
