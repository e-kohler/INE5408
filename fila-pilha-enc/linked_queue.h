// Copyright 2017 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
/**
 * Implementação de uma fila encadeada com template, (FIFO).
 */
template <typename T>
class LinkedQueue {
 public:
  LinkedQueue();

  ~LinkedQueue();

  void clear();  // limpar

  void enqueue(const T& data);  // enfilerar

  T dequeue();  // desenfilerar

  T& front() const;  // primeiro dado

  T& back() const;  // último dado

  bool empty() const;  // fila vazia

  std::size_t size() const;  // tamanho

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
    Node* next_;
  };

  Node* head_;        // nodo-cabeça
  Node* tail_;        // nodo-fim
  std::size_t size_;  // tamanho
};
/**
 * Construtor. Determina o valor dos atributos na criação do objeto.
 */
template <typename T>
LinkedQueue<T>::LinkedQueue() {
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}
/**
 * Destrutor. Deleta o array contents.
 */
template <typename T>
LinkedQueue<T>::~LinkedQueue() {
  clear();
}
/**
 * Coloca um elemento no fim da fila.
 * \param referência de um dado.
 */
template <typename T>
void LinkedQueue<T>::enqueue(const T& data) {
  Node* input = new Node(data, nullptr);
  if (empty()) {
    head_ = input;
    tail_ = input;
    size_++;
  } else {
    tail_->next(input);
    tail_ = input;
    size_++;
  }
}
/**
 * Retira o elemento do começo da fila.
 * \return elemento do começo da fila.
 */
template <typename T>
T LinkedQueue<T>::dequeue() {
  if (empty()) {
    throw std::out_of_range("Fila vazia");
  } else {
    Node* removed = head_;
    T output = head_->data();
    head_ = head_->next();
    delete removed;
    size_--;
    return output;
  }
}
/**
 * Retorna o membro do início da fila.
 *\return referência do membro do início.
 */
template <typename T>
T& LinkedQueue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Fila vazia");
  } else {
    return head_->data();
  }
}
/**
 * Retorna o membro do fim da fila.
 *\return referência do membro do final.
 */
template <typename T>
T& LinkedQueue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Fila vazia");
  } else {
    return tail_->data();
  }
}
/**
 * Limpa a fila.
 */
template <typename T>
void LinkedQueue<T>::clear() {
  while (!empty()) {
    dequeue();
  }
}
/**
 * Retorna o tamanho da fila.
 * \return tamanho da fila.
 */
template <typename T>
std::size_t LinkedQueue<T>::size() const {
  return size_;
}
/**
 * Verifica se a fila está vazia.
 *\return booleano
 */
template <typename T>
bool LinkedQueue<T>::empty() const {
  return size_ == 0;
}
}  // namespace structures

#endif
