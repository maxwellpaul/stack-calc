#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface

public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == 0;
  }

  //EFFECTS: returns the number of elements in this List
  int size() const {
    int size = 0;
    if (!empty()) {
      for (Iterator i(begin()); i != end(); ++i) {
        ++size;
      }
    }
    return size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the first element in the list
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the last element in the list
  T & back() {
    assert(!empty());
    return last->datum;
  }
  //MODIFIES: this
  //EFFECTS:  inserts i into the front of the list
  void push_front(const T &datum) {
    Node* new_first = new Node;
    Node* old_first = first;

    if (!empty()){
      old_first->prev = new_first;
      new_first->next = old_first;
    } else {
      last = new_first;
      new_first->next = 0;
    }
    first = new_first;

    first->prev = 0;
    first->datum = datum;

    new_first = 0;
    old_first = 0;
  }

  //MODIFIES: this
  //EFFECTS:  inserts i into the back of the list
  void push_back(const T &datum) {
    Node* new_last = new Node;
    Node* old_last = last;

    if (!empty()){
      old_last->next = new_last;
      new_last->prev = old_last;
    } else {
      first = new_last;
      new_last->prev = 0;
    }
    last = new_last;

    last->next = 0;
    last->datum = datum;

    new_last = 0;
    old_last = 0;
  }

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {

    assert(!empty());
    Node* new_front = first->next;

    if (new_front) {
      new_front->prev = 0;
    }

    if (first == last) {
      last = 0;
    }

    delete first;

    first = new_front;

    new_front = 0;
  }

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node* new_last = last->prev;

    if (new_last) {
      new_last->next = 0;
    }

    if (first == last) {
      first = 0;
    }

    delete last;

    last = new_last;

    new_last = 0;
  }

  //MODIFIES  *this
  //EFFECTS   makes a copy of other to this, replacing all data previously
  //          held in this
  List& operator= (const List& other) {
    pop_all();
    copy_all(other);
    return *this;
  }

  //MODIFIES  this
  //EFFECTS   initializes the new list exactly the same as the old list
  List(const List& other)
  : first(0), last(0) 
  { copy_all(other); }

  //MODIFIES  this
  //EFFECTS   initializes an empty list
  List()
  : first(0), last(0) {}

  //MODIFIES  this
  //EFFECTS   destructor that cleans up all data and erases the entire list
  ~List() {
    pop_all();
  }
private:

  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //MODIFIES: this
  //EFFECTS:  copies all nodes from l to this
  void copy_all(const List<T> &other) {
    for (Iterator i(other.begin()); i != other.end(); ++i) push_back(*i);
  }

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  void pop_all() {
  while (!empty()) pop_front();
  }
  Node *first;   // points to first Node in list, or 0 if list is empty
  Node *last;    // points to last Node in list, or 0 if list is empty

public:
  ////////////////////////////////////////
	class Iterator {

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    //EFFECTS returns the result of *this != rhs
    bool operator!= (const Iterator& rhs) const {
      if (this->node_ptr != rhs.node_ptr) return true;
      return false;
    }

    //EFFECTS returns the result of *this != rhs
    bool operator== (const Iterator& rhs) const {
      if (!(*this != rhs)) return true;
      return false;
    }

    //EFFECTS returns the "dereferenced" Iterator class object,
    //        AKA just returns the datum that the Iterator points to
    T& operator* (){
      assert(node_ptr);
      return node_ptr->datum;
    }

    //MODIFIES  this
    //EFFECTS   moves the node_ptr in the Iterator object to the next node
    Iterator& operator++ () {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }
    
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p)
    : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first node
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    if (last){
      return Iterator(last->next);
    }
    return Iterator(first);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: this, may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    if (!(i.node_ptr)) return;

    if (i.node_ptr->prev && i.node_ptr->next) {
      i.node_ptr->prev->next = i.node_ptr->next;
      i.node_ptr->next->prev = i.node_ptr->prev;
    }
    else if (i.node_ptr->prev) {
      first = i.node_ptr->prev;
      i.node_ptr->prev->next = 0;
    }
    else if (i.node_ptr->next) {
      last = i.node_ptr->next;
      i.node_ptr->next->prev = 0;
    }
    else if (!i.node_ptr->next && !i.node_ptr->prev) {
      last = 0;
      first = 0;
    }
    delete i.node_ptr; i.node_ptr = 0;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if (i.node_ptr == first) push_front(datum);
    else {
      Node* new_node_ptr = new Node;
     //set up new node
      new_node_ptr->datum = datum;
      new_node_ptr->next = i.node_ptr;
      new_node_ptr->prev = i.node_ptr->prev;

      //set the prev node to point to new node
      i.node_ptr->prev->next = new_node_ptr;

      //set the next node to point to the new node
      i.node_ptr->prev = new_node_ptr;
    }
  }

};//List

#endif
