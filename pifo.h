#ifndef PIFO_H_
#define PIFO_H_

#include <iostream>
#include <queue>

template <typename ElementType>
class PIFO {
 public:
  /// Push element of ElementType into PIFO
  void push(const ElementType & element) { queue_.push(element); }

  /// Pop and return element from the top of the PIFO
  ElementType pop(void) {
    if (not queue_.empty()) {
      auto ret = queue_.top();
      queue_.pop();
      return ret;
    } else {
      std::cout << "Returning empty element\n";
      return ElementType();
    }
  }

  /// Utility method to print queue contents
  void print_queue() const {
    // Copy priority_queue and then iterate over it
    auto shadow_copy = queue_;
    while (not shadow_copy.empty()) {
      std::cout << shadow_copy.top() << std::endl;
      shadow_copy.pop();
    }
    std::cout << std::endl;
  }
 private:
  /// Underlying sorted array of ElementType aka. priority_queue
  std::priority_queue<ElementType> queue_ = std::priority_queue<ElementType>();
};

#endif  // PIFO_H_
