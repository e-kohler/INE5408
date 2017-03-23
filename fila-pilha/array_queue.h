// Copyright 2016 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
/**
 * Implementação de uma fila com template, (FIFO).
 */
template<typename T>
class ArrayQueue {
 public:
    ArrayQueue();

    explicit ArrayQueue(std::size_t max);

    ~ArrayQueue();

    void enqueue(const T& data);

    T dequeue();

    T& back();

    void clear();

    std::size_t size();

    std::size_t max_size();

    bool empty();

    bool full();

 private:
    T* contents;  // Armazena os dados da fila.
    std::size_t size_;  // Guarda o tamanho atual da fila.
    std::size_t max_size_;  // Guarda o tamanho máximo da fila.
    int last_, first_;  // Variáveis para o último e primeiro elementos.
    static const auto DEFAULT_SIZE = 10u;  // Guarda o tamanho padrão da fila.
};
/**
 * Construtor. Determina o valor dos atributos na criação do objeto caso não haja parâmetros.
 */
template<typename T>
ArrayQueue<T>::ArrayQueue() {
	max_size_ = DEFAULT_SIZE;
	size_ = 0;
	contents = new T[max_size];
	last_ = -1;
	first_ = 0;
}
/**
 * Construtor. Determina o valor das variáveis e usa o parâmetro passado como tamanho máximo.
 */
template<typename T>
ArrayQueue<T>::ArrayQueue(std::size_t max) {
	max_size_ = max;
	size_ = 0;
	contents = new T[max_size_];
	last_ = -1;
	first_ = 0;
}
/**
 * Destrutor. Deleta o array contents.
 */
template<typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}
/**
 * Coloca um elemento no fim da fila.
 * \param referência de um dado.
 */
template<typename T>
void ArrayQueue<T>::enqueue(const T& data) {
	if (full()) {
		throw std::out_of_range("Fila cheia");
	}
	size_++;
	last_++;
	contents[last_] = data;
}
/**
 * Retira o elemento do começo da fila.
 * \return elemento do começo da fila.
 */
template<typename T>
T ArrayQueue<T>::dequeue() {
	if(empty()) {
		throw std::out_of_range("Fila vazia");
	}
	size_--;
	first_++;
	return contents[first_-1];
}
/**
 * Retorna o membro do fim da fila.
 *\return referência do membro do final.
 */
template<typename T>
T& ArrayQueue<T>::back() {
	if(empty()) {
		throw std::out_of_range("Fila vazia");
	}
	return contents[last_];
}
/**
 * Limpa a fila.
 */
template<typename T>
void ArrayQueue<T>::clear() {
	size_ = 0;
	first_ = 0;
	last_ = -1;
}
/**
 * Retorna o tamanho da fila.
 * \return tamanho da fila.
 */
template<typename T>
std::size_t ArrayQueue<T>::size() {
	return size_;
}
/**
 * Retorna o tamanho máximo da fila.
 * \return tamanho máximo da fila.
 */
template<typename T>
std::size_t ArrayQueue<T>::max_size() {
	return max_size_;
}
/**
 * Verifica se a fila está vazia.
 *\return booleano
 */
template<typename T>
bool ArrayQueue<T>::empty() {
	return size_ == 0;
}
/**
 * Verifica se a fila está cheia.
 * \return booleano.
 */
template<typename T>
bool ArrayQueue<T>::full() {
	return size_ == max_size_;
}
}  // namespace structures

#endif
