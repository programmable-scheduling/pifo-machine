#ifndef OPTIONAL_H_
#define OPTIONAL_H_

#include <cassert>

/// Simplistic implementation of Optional types
/// Boost's optional class is far too complicated
/// for my liking and includes too many implicit
/// type casts.
template <class T>
class Optional {
 public:
  T get() const { assert(initialized_); return value_; }
  void set(T t_value) { value_ = t_value; initialized_ = true; }

 private:
  bool initialized_ = false;
  T value_ = {};
};

#endif  // OPTIONAL_H_
