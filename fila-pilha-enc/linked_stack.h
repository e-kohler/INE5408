// Copyright 2017 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {
/**
 * Implementação de uma pilha encadeada.
 */
template <typename T>
class LinkedStack {
 public:
  LinkedStack();

  ~LinkedStack();

  void clear();  // limpa pilha

  void push(const T& data);  // empilha

  T pop();  // desempilha

  T& top() const;  // dado no topo

  bool empty() const;  // pilha vazia

  std::size_t size() const;  // tamanho da pilha

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

  Node* top_;         // nodo-topo
  std::size_t size_;  // tamanho
};
/**
 * Construtor. Determina o valor das variáveis e usa o parâmetro passado como
 * tamanho máximo.
 */
template <typename T>
LinkedStack<T>::LinkedStack() {
  top_ = nullptr;
  size_ = 0;
}
/**
 * Destrutor. Deleta o array contents.
 */
template <typename T>
LinkedStack<T>::~LinkedStack() {
  clear();
}
/**
 * Coloca um elemento no topo da pilha.
 * \param referência de um dado.
 */
template <typename T>
void LinkedStack<T>::push(const T& data) {
  Node* input = new Node(data);
  if (empty()) {
    input->next(nullptr);
  } else {
    input->next(top_);
  }
  top_ = input;
  size_++;
}
/**
 * Retira o elemento do topo da pilha.
 * \return elemento do topo da pilha.
 */
template <typename T>
T LinkedStack<T>::pop() {
  Node* popped = top_;
  if (empty()) {
    throw std::out_of_range("Pilha vazia");
  } else {
    T output = top_->data();
    top_ = top_->next();
    size_--;
    delete popped;
    return output;
  }
}
/**
 * Retorna o membro do topo da pilha.
 *\return referência do membro do topo.
 */
template <typename T>
T& LinkedStack<T>::top() const {
  if (empty()) {
    throw std::out_of_range("Pilha vazia");
  } else {
    return top_->data();
  }
}
/**
 * Limpa a pilha.
 */
template <typename T>
void LinkedStack<T>::clear() {
  while (!empty()) {
    pop();
  }
}
/**
 * Retorna o tamanho da pilha.
 * \return tamanho da pilha.
 */
template <typename T>
std::size_t LinkedStack<T>::size() const {
  return size_;
}
/**
 * Verifica se a pilha está vazia.
 *\return booleano
 */
template <typename T>
bool LinkedStack<T>::empty() const {
  return size_ == 0;
}
}  // namespace structures
#endif
