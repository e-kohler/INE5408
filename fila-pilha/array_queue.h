#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
public:
    ArrayQueue();

    ArrayQueue(std::size_t max);

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
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int last_, first_;
    const static auto DEFAULT_SIZE = 10u;
};

template<typename T>
ArrayQueue<T>::ArrayQueue(){
	max_size_ = DEFAULT_SIZE;
	size_ = 0;
	contents = new T[max_size];
	last_ = -1;
	first_ = 0;
}

template<typename T>
ArrayQueue<T>::ArrayQueue(std::size_t max){
	max_size_ = max;
	size_ = 0;
	contents = new T[max_size_];
	last_ = -1;
	first_ = 0;
}

template<typename T>
ArrayQueue<T>::~ArrayQueue(){
    delete[] contents;
}

template<typename T>
void ArrayQueue<T>::enqueue(const T& data){
	if (full()){
		throw std::out_of_range("Fila cheia");
	}
	size_++;
	last_++;
	contents[last_] = data;
}

template<typename T>
T ArrayQueue<T>::dequeue(){
	if(empty()){
		throw std::out_of_range("Fila vazia");
	}
	size_--;
	first_++;
	return contents[first_-1];
}

template<typename T>
T& ArrayQueue<T>::back(){
	if(empty()){
		throw std::out_of_range("Fila vazia");
	}
	return contents[last_];
}

template<typename T>
void ArrayQueue<T>::clear(){
	size_ = 0;
	first_ = 0;
	last_ = -1;
}

template<typename T>
std::size_t ArrayQueue<T>::size(){
	return size_;
}

template<typename T>
std::size_t ArrayQueue<T>::max_size(){
	return max_size_;
}

template<typename T>
bool ArrayQueue<T>::empty(){
	return size_ == 0;
}

template<typename T>
bool ArrayQueue<T>::full(){
	return size_ == max_size_;
}
}

#endif
