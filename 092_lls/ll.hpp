#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(new Node()), tail(new Node()), size(0) {
    head->next = tail;
    tail->prev = head;
  }

  LinkedList(const LinkedList & rhs) :
      head(new Node()), tail(new Node()), size(rhs.size) {
    head->next = tail;
    tail->prev = head;
    for (Node * i = rhs.head->next; i != rhs.tail; i = i->next) {
      addBack(i->data);
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this == &rhs) {
      return *this;
    }
    myclear();
    head = new Node();
    tail = new Node();
    size = rhs.size;
    head->next = tail;
    tail->prev = head;
    for (Node * i = rhs.head->next; i != rhs.tail; i = i->next) {
      addBack(i->data);
    }
    return *this;
  }

  ~LinkedList() { myclear(); }

  void myclear() {
    Node * i = head->next;
    while (i != tail) {
      Node * temp = i->next;
      delete i;
      i = temp;
    }
    delete head;
    delete tail;
  }

  void addFront(const T & item) {
    Node * node = new Node(item, head->next, head);
    head->next->prev = node;
    head->next = node;
    size++;
  }

  void addBack(const T & item) {
    Node * node = new Node(item, tail, tail->prev);
    tail->prev->next = node;
    tail->prev = node;
    size++;
  }

  bool remove(const T & item) {
    for (Node * i = head->next; i != tail; i = i->next) {
      if (i->data == item) {
        i->prev->next = i->next;
        i->next->prev = i->prev;
        delete i;
        size--;
        return true;
      }
    }
    return false;
  }

  T & operator[](int index) throw(std::exception) {
    if (index < 0 || index >= size) {
      throw std::exception();
    }
    Node * node = head;
    for (int i = 0; i <= index; i++) {
      node = node->next;
    }
    return node->data;
  }

  const T & operator[](int index) const throw(std::exception) {
    if (index < 0 || index >= size) {
      throw std::exception();
    }
    Node * node = head;
    for (int i = 0; i <= index; i++) {
      node = node->next;
    }
    return node->data;
  }

  int find(const T & item) const {
    int index = 0;
    for (Node * i = head->next; i != tail; i = i->next) {
      if (i->data == item) {
        return index;
      }
      index++;
    }
    return -1;
  }

  int getSize() const { return size; }
};

#endif
