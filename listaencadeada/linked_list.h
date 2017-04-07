// Copyright 2017 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
/**
 * Implementation of a template linked list.
 */
template <typename T>
class LinkedList {
 public:
  LinkedList();
  ~LinkedList();
  void clear();
  void push_back(const T& data);
  void push_front(const T& data);
  void insert(const T& data, std::size_t index);
  void insert_sorted(const T& data);
  T& at(std::size_t index);
  T pop(std::size_t index);
  T pop_back();
  T pop_front();
  void remove(const T& data);
  bool empty() const;
  bool contains(const T& data) const;
  std::size_t find(const T& data) const;
  std::size_t size() const;

 private:
  class Node {
   public:
    explicit Node(const T& data) : data_{data} {}

    Node(const T& data, Node* next) : data_{data}, next_{next} {}

    T& data() { return data_; }

    const T& data() const { return data_; }

    Node* next() { return next_; }

    const Node* next() const { return next_; }

    void next(Node* node) { next_ = node; }

   private:
    T data_;
    Node* next_{nullptr};
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
LinkedList<T>::LinkedList() {
  head = nullptr;
  size_ = 0;
}
/**
 * Destructor. Deletes the contents[] array.
 */
template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}
/**
 * Clears the list.
 */
template <typename T>
void LinkedList<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}
/**
 * Checks if the list is empty.
 * \return boolean
 */
template <typename T>
bool LinkedList<T>::empty() const {
  return size_ == 0;
}
/**
 * Adds an element to the front of the list.
 */
template <typename T>
void LinkedList<T>::push_front(const T& data) {
  Node* first = new Node(data);
  if (first == nullptr) {
    throw std::out_of_range("Lista cheia.");
  }
  first->next(head);
  head = first;
  size_++;
}
/**
 * Removes the first element.
 * \return The first element of type T.
 */
template <typename T>
T LinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  } else {
    Node* first = head;
    T out_ = first->data();
    head = first->next();
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
void LinkedList<T>::insert(const T& data, std::size_t index) {
  Node* input;
  Node* prev;
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
    input->next(prev->next());
    prev->next(input);
    size_++;
  }
}
/**
 * Takes an element out by its index.
 * \param index element index.
 */
template <typename T>
T LinkedList<T>::pop(std::size_t index) {
  T output_;
  Node* popped;
  Node* prev;
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
    output_ = popped->data();
    prev->next(popped->next());
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
void LinkedList<T>::insert_sorted(const T& data) {
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
void LinkedList<T>::push_back(const T& data) {
  insert(data, size());
}
/**
 * Removes the last element.
 */
template <typename T>
T LinkedList<T>::pop_back() {
  return pop(size() - 1);
}
/**
 * Returns a reference to the element at the specified index.
 */
template <typename T>
T& LinkedList<T>::at(std::size_t index) {
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
 * Checks if the list has a certain element, and if so, returns its index.
 * \return specified element index.
 */
template <typename T>
std::size_t LinkedList<T>::find(const T& data) const {
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
void LinkedList<T>::remove(const T& data) {
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
bool LinkedList<T>::contains(const T& data) const {
  return find(data) != size();
}
/**
 * Returns the list current size.
 */
template <typename T>
std::size_t LinkedList<T>::size() const {
  return size_;
}
}  // namespace structures
#endif