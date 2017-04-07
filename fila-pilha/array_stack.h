// Copyright 2017 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {
/**
 * Implementação de uma pilha com template (LIFO).
 */
template<typename T>
class ArrayStack {
 public:
    ArrayStack();

    explicit ArrayStack(std::size_t max);

    ~ArrayStack();

    void push(const T& data);

    T pop();

    T& top();

    void clear();

    std::size_t size();

    std::size_t max_size();

    bool empty();

    bool full();

 private:
    static const auto DEFAULT_SIZE = 10u;  // Tamanho máximo da pilha padrão.
    T* contents;  // Armazena os elementos da pilha
    int top_;  // Armazena o índice do elemento do topo
    std::size_t max_size_;  // Tamanho máximo da pilha
};
/**
 * Construtor. Determina o valor dos atributos na criação do objeto caso não haja parâmetros.
 */
template<typename T>
ArrayStack<T>::ArrayStack() {
	max_size_ = DEFAULT_SIZE;
	contents = new T[max_size];
	top_ = -1;
}
/**
 * Construtor. Determina o valor das variáveis e usa o parâmetro passado como tamanho máximo.
 */
template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
	max_size_ = max;
	contents = new T[max_size_];
	top_ = -1;
}
/**
 * Destrutor. Deleta o array contents.
 */
template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}
/**
 * Coloca um elemento no topo da pilha.
 * \param referência de um dado.
 */
template<typename T>
void ArrayStack<T>::push(const T& data) {
	if(full()) {
		throw std::out_of_range("Pilha cheia");
	}
	top_++;
	contents[top_] = data;
}
/**
 * Retira o elemento do topo da pilha.
 * \return elemento do topo da pilha.
 */
template<typename T>
T ArrayStack<T>::pop() {
	if(empty()) {
		throw std::out_of_range("Pilha vazia");
	}
	top_--;
	return contents[top_+1];
}
/**
 * Retorna o membro do topo da pilha.
 *\return referência do membro do topo.
 */
template<typename T>
T& ArrayStack<T>::top() {
	if(empty()) {
		throw std::out_of_range("Pilha vazia");
	}
	return contents[top_];
}
/**
 * Limpa a pilha.
 */
template<typename T>
void ArrayStack<T>::clear() {
	top_ = -1;
}
/**
 * Retorna o tamanho da pilha.
 * \return tamanho da pilha.
 */
template<typename T>
std::size_t ArrayStack<T>::size() {
	return top_+1;
}
/**
 * Retorna o tamanho máximo da pilha.
 * \return tamanho máximo da pilha.
 */
template<typename T>
std::size_t ArrayStack<T>::max_size() {
	return max_size_;
}
/**
 * Verifica se a pilha está vazia.
 *\return booleano
 */
template<typename T>
bool ArrayStack<T>::empty() {
	return top_ == -1;
}
/**
 * Verifica se a pilha está cheia.
 * \return booleano.
 */
template<typename T>
bool ArrayStack<T>::full() {
	return top_ == max_size_-1;
}
}  // namespace structures
#endif
