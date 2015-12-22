#ifndef STACK_H
#define STACK_H
#include "List.h"
#include <cstddef>
#include <cassert>

template <typename T>
class Stack {
  //OVERVIEW: a templated, linked-list-based stack
  // The T is type of value stored, and it must implement operator<<

 public:
  //MODIFIES  this
  //EFFECTS   initializes a Stack type object
  Stack()
  : list(List<T>()) {}

  //EFFECTS:  returns true if the stack is empty
  bool empty() const {
    return list.empty();
  }

  //EFFECTS: returns the number of elements in this Stack
  int size() const {
    return list.size();
  }

  //REQUIRES: stack is non-empty. Assert false if it is empty.
  //MODIFIES: this
  //EFFECTS:  removes the item at the top and returns it.
  T pop() {
    assert(!empty());
    T result = list.front();
    list.pop_front();
    return result;
  }

  //REQUIRES: stack be non-empty. Assert false if it is empty.
  //EFFECTS:  returns a reference the top element from the stack without
  // popping it.
  
  T & top() {
    assert(!empty());
    return list.front();
  }

  //MODIFIES: this
  //EFFECTS: pushes an item onto the top of the stack
  void push(const T &item) {
    list.push_front(item);
  }

  template <typename Predicate>
  int count_if(Predicate pred) const {

    int count = 0;

    for (typename List<T>::Iterator i(list.begin()); i != list.end(); ++i){
      if (pred(*i)) ++count;
    }
    return count;
  }

  //friend declaration for ostram &operator<<
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Stack<U> &obj);

private:
  /* You must make use of List's interface to implement the stack.
   * You must not make changes to the private section.
   */
  List<T> list;
};

template <typename U>
std::ostream &operator<<(std::ostream &os, const Stack<U> &obj) {
  for (typename List<U>::Iterator i(obj.list.begin()); i != obj.list.end(); ++i){
    os << *i << " ";
  }
  return os;
}
#endif /* STACK_H */
