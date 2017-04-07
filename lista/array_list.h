// Copyright 2017 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
/**
 * Implementation of a template list.
 */
template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;  // Stores the list data.
    std::size_t size_;  // Actual list size.
    std::size_t max_size_;  // Maximum list size.
    static const auto DEFAULT_MAX = 10u;  // Default maximum size.
};
/**
 * Constructor. Sets the attributes values.
 */
template<typename T>
ArrayList<T>::ArrayList() {
	max_size_ = DEFAULT_MAX;
	size_ = 0;
	contents = new T[max_size_];
}
/**
 * Constructor. Sets the attributes values with
 * the maximum size as a parameter.
 */
template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size) {
	max_size_ = max_size;
	size_ = 0;
	contents = new T[max_size_];
}
/**
 * Destructor. Deletes the contents[] array.
 */
template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] contents;
}
/**
 * Clears the list.
 */
template<typename T>
void ArrayList<T>::clear() {
	size_ = 0;
}
/**
 * Adds an element to the end of the list.
 */
template<typename T>
void ArrayList<T>::push_back(const T& data) {
    insert(data, size_);
}
/**
 * Adds an element to the front of the list.
 */
template<typename T>
void ArrayList<T>::push_front(const T& data) {
	insert(data, 0);
}
/**
 * Inserts an element in the specified location.
 * \param data data reference;
 * \param index index where the element will be put in.
 */
template<typename T>
void ArrayList<T>::insert(const T& data, std::size_t index) {
	if (full()) {
		throw std::out_of_range("Lista cheia");
	}
	if (index > size_) {
	    throw std::out_of_range("Index inválido");
	}
	for(int i = size_; i > index; i--) {
        contents[i] = contents[i-1];
	}
	contents[index] = data;
	size_++;
}
/**
 * Inserts an element respecting numeric progression.
 * \param data data.
 */
template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
    std::size_t  pos_ = 0;
	if (full()) {
		throw std::out_of_range("Lista cheia");
	}
	for(int i = 0; i < size_; i++) {
		if (data > contents[i]) {
		    pos_++;
		}
	}
	insert(data, pos_);
}
/**
 * Takes an element out by its index.
 * \param index element index.
 */
template<typename T>
T ArrayList<T>::pop(std::size_t index) {
	T value_;
	if (empty()) {
		throw std::out_of_range("Lista vazia");
	}
	if (index > size_-1) {
		throw std::out_of_range("Parâmetro inválido");
	}
	value_ = contents[index];
	for(int i = index; i < size_-1; i++) {
		contents[i] = contents[i+1];
	}
	size_--;
	return value_;
}
/**
 * Removes the last element.
 */
template<typename T>
T ArrayList<T>::pop_back() {
	return pop(size_-1);
}
/**
 * Removes the first element.
 */
template<typename T>
T ArrayList<T>::pop_front() {
	return pop(0);
}
/**
 * Removes an element by its content.
 * \param data data.
 */
template<typename T>
void ArrayList<T>::remove(const T& data) {
	int index_;
	for(int i = 0; i < size_; i++) {
		if(contents[i] == data) {
			index_ = i;
		}
	}
	pop(index_);
}
/**
 * Checks if the list is full.
 * \return boolean
 */
template<typename T>
bool ArrayList<T>::full() const {
	return size_ == max_size_;
}
/**
 * Checks if the list is empty.
 * \return boolean
 */
template<typename T>
bool ArrayList<T>::empty() const {
	return size_ == 0;
}
/**
 * Checks if the list contains a certain element by its content.
 * \return boolean
 */
template<typename T>
bool ArrayList<T>::contains(const T& data) const {
	return find(data) != size();
}
/**
 * Checks if the list has a certain element, and if so, returns its index.
 * \return specified element index.
 */
template<typename T>
std::size_t ArrayList<T>::find(const T& data) const {
	std::size_t index_ = size();
	for(int i = 0; i < size_; i++) {
		if(contents[i] == data) {
			index_ = i;
		}
	}
	return index_;
}
/**
 * Returns the list actual size.
 */
template<typename T>
std::size_t ArrayList<T>::size() const {
	return size_;
}
/**
 * Returns the list maximum size.
 */
template<typename T>
std::size_t ArrayList<T>::max_size() const {
	return max_size_;
}
/**
 * Returns a reference to the element at the specified index.
 */
template<typename T>
T& ArrayList<T>::at(std::size_t index) {
    if (index > size_-1) {
        throw std::out_of_range("Index inválido");
    }
	return contents[index];
}
/**
 * Returns a reference to the element at the specified index.
 */
template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
    return at(index);
}
/**
 * Returns a reference to the element at the specified index.
 */
template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
	return at(index);
}
/**
 * Returns a reference to the element at the specified index.
 */
template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
    return at(index);
}
}  // namespace structures

#endif
