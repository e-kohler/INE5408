// Copyright 2017 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
/**
* Implementation of a template doubly linked list.
*/
template <typename T>
class DoublyLinkedList {
 public:
  DoublyLinkedList();
  ~DoublyLinkedList();
  void clear();

  void push_back(const T& data);
  void push_front(const T& data);
  void insert(const T& data, std::size_t index);
  void insert_sorted(const T& data);

  T pop(std::size_t index);
  T pop_back();
  T pop_front();
  void remove(const T& data);

  bool empty() const;
  bool contains(const T& data) const;

  T& at(std::size_t index);
  const T& at(std::size_t index) const;

  std::size_t find(const T& data) const;
  std::size_t size() const;

 private:
  class Node {
   public:
    explicit Node(const T& data) : data_{data} {}
    Node(const T& data, Node* next) : data_{data}, next_{next} {}
    Node(const T& data, Node* next, Node* prev)
        : data_{data}, next_{next}, prev_{prev} {}

    T& data() { return data_; }
    const T& data() const { return data_; }

    Node* prev() { return prev_; }
    const Node* prev() const { return prev_; }
    void prev(Node* node) { prev_ = node; }

    Node* next() { return next_; }
    const Node* next() const { return next_; }
    void next(Node* node) { next_ = node; }

   private:
    T data_;
    Node* next_{nullptr};
    Node* prev_{nullptr};
  };

  Node* end() {
    auto it = head;
    for (auto i = 1u; i < size(); ++i) {
      it = it->next();
    }
    return it;
  }
  Node* head{nullptr};
  std::size_t size_{0u};
};
/**
 * Constructor. Sets the attributes values.
 */
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  head = nullptr;
  size_ = 0;
}
/**
 * Destructor. Deletes the contents[] array.
 */
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}
/**
 * Clears the list.
 */
template <typename T>
void DoublyLinkedList<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}
/**
 * Checks if the list is empty.
 * \return boolean
 */
template <typename T>
bool DoublyLinkedList<T>::empty() const {
  return size_ == 0;
}
/**
 * Adds an element to the front of the list.
 */
template <typename T>
void DoublyLinkedList<T>::push_front(const T& data) {
  Node* first = new Node(data);
  Node* next;
  if (first == nullptr) {
    throw std::out_of_range("Lista cheia.");
  } else if (!empty()) {
    next = head;
    next->prev(first);
  }
  first->prev(nullptr);
  first->next(head);
  head = first;
  size_++;
}
/**
 * Removes the first element.
 * \return The first element of type T.
 */
template <typename T>
T DoublyLinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  } else {
    Node* first = head;
    T out_ = first->data();
    head = first->next();
    if (head != nullptr) {
      head->prev(nullptr);
    }
    delete first;
    size_--;
    return out_;
  }
}
/**
 * Inserts an element in the specified location.
 * \param data data reference;
 * \param index index where the element will be put in.
 */
template <typename T>
void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
  Node* input;
  Node* prev;
  Node* next;
  if (index > size()) {
    throw std::out_of_range("Index inválido");
  } else if (index == 0) {
    push_front(data);
  } else {
    input = new Node(data);
    if (input == nullptr) {
      throw std::out_of_range("Lista cheia.");
    }
    prev = head;
    for (int i = 0; i < index - 1; i++) {
      prev = prev->next();
    }
    next = prev->next();
    input->next(next);
    if (next != nullptr) {
      next->prev(input);
    }
    input->prev(prev);
    prev->next(input);
    size_++;
  }
}
/**
 * Takes an element out by its index.
 * \param index element index.
 */
template <typename T>
T DoublyLinkedList<T>::pop(std::size_t index) {
  T output_;
  Node* popped;
  Node* prev;
  Node* next;
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  } else if (index > size() - 1) {
    throw std::out_of_range("Parâmetro inválido");
  } else if (index == 0) {
    return pop_front();
  } else {
    prev = head;
    for (int i = 0; i < index - 1; i++) {
      prev = prev->next();
    }
    popped = prev->next();
    next = popped->next();
    output_ = popped->data();
    prev->next(next);
    if (next != nullptr) {
      next->prev(prev);
    }
    size_--;
    delete popped;
    return output_;
  }
}
/**
 * Inserts an element respecting a specific progression.
 * \param data data.
 */
template <typename T>
void DoublyLinkedList<T>::insert_sorted(const T& data) {
  Node* current;
  if (empty()) {
    push_front(data);
  } else {
    current = head;
    std::size_t pos;
    for (pos = 0; pos < size() && data > current->data(); pos++) {
      current = current->next();
    }
    insert(data, pos);
  }
}
/**
 * Adds an element to the end of the list.
 */
template <typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
  insert(data, size());
}
/**
 * Removes the last element.
 */
template <typename T>
T DoublyLinkedList<T>::pop_back() {
  return pop(size() - 1);
}
/**
 * Returns a reference to the element at the specified index.
 */
template <typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
  Node* current;
  if (index > size() - 1) {
    throw std::out_of_range("Index inválido");
  } else if (index == 0) {
    current = head;
    return current->data();
  } else {
    current = head;
    for (int i = 0; i < index; i++) {
      current = current->next();
    }
    return current->data();
  }
}
/**
 * Returns a reference to the element at the specified index.
 */
template <typename T>
const T& DoublyLinkedList<T>::at(std::size_t index) const {
  return at(index);
}
/**
 * Checks if the list has a certain element, and if so, returns its index.
 * \return specified element index.
 */
template <typename T>
std::size_t DoublyLinkedList<T>::find(const T& data) const {
  Node* current = head;
  std::size_t index = size();
  for (std::size_t i = 0; i < size(); i++) {
    if (current->data() == data) {
      index = i;
      break;
    }
    if (i != size()) {
      current = current->next();
    }
  }
  return index;
}
/**
 * Removes an element by its content.
 * \param data data.
 */
template <typename T>
void DoublyLinkedList<T>::remove(const T& data) {
  std::size_t test = find(data);
  if (test != size()) {
    pop(test);
  }
}
/**
 * Checks if the list contains a certain element by its content.
 * \return boolean
 */
template <typename T>
bool DoublyLinkedList<T>::contains(const T& data) const {
  return find(data) != size();
}
/**
 * Returns the list current size.
 */
template <typename T>
std::size_t DoublyLinkedList<T>::size() const {
  return size_;
}
}  // namespace structures

#endif
