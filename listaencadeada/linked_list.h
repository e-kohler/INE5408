// Copyright 2016 Eduardo Kohler

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
/**
 * Implementation of a template linked list.
 */
template<typename T>
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
     	explicit Node(const T& data):
    	    data_{data}
        {}

     	Node(const T& data, Node* next):
        	data_{data},
        	next_{next}
        {}

    	T& data() {
        	return data_;
        }

     	const T& data() const {
     		return data_;
        }

    	Node* next() {
      		return next_;
        }

        const Node* next() const {
        	return next_;
        }

        void next(Node* node) {
        	next_ = node;
        }
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
template<typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	size_ = 0;
}
/**
 * Destructor. Deletes the contents[] array.
 */
template<typename T>
LinkedList<T>::~LinkedList() {
	clear();
}
/**
 * Clears the list.
 */
template<typename T>
void LinkedList<T>::clear() {
	size_ = 0;
}
/**
 * Checks if the list is empty.
 * \return boolean
 */
template<typename T>
bool LinkedList<T>::empty() const {
	return size_ == 0;
}
/**
 * Adds an element to the front of the list.
 */
template<typename T>
void LinkedList<T>::push_front(const T& data) {
	Node* first_;
	first_ = new Node(data, head);
	head = first_;
	size_++;
}
/**
 * Removes the first element.
 * \return The first element of type T.
 */
template<typename T>
T LinkedList<T>::pop_front() {
	if (empty()) {
		throw std::out_of_range("Lista vazia");
	} else {
		Node* first_ = head;
		T out_ = first_->data();
		head = first_->next();
		delete first_;
		size_--;
		return out_;
	}
}
/**
 * Inserts an element in the specified location.
 * \param data data reference;
 * \param index index where the element will be put in.
 */
template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
	Node* input_;
	Node* prev_;
	if (index > size()) {
		throw std::out_of_range("Index inválido");
	} else if (index == 1) {
		return push_front(data);
	} else {
		input_ = new Node(data);
		prev_ = head;
		for (int i = 0; i < index-2; i++) {
			prev_ = prev_->next();
		}
		input_->next(prev_->next());
		prev_->next(input_);
		size_++;
	}
}
/**
 * Takes an element out by its index.
 * \param index element index.
 */
template<typename T>
T LinkedList<T>::pop(std::size_t index) {
	T output_;
	Node* popped_;
	Node* prev_;
	if (empty()) {
		throw std::out_of_range("Lista vazia");
	} else if (index > size_) {
		throw std::out_of_range("Parâmetro inválido");
	} else if (index == 1) {
		return pop_front();
	} else {
		prev_ = head;
		for (int i = 0; i < index-2; i++) {
			prev_ = prev_->next();
		}
		popped_ = prev_->next();
		output_ = popped_->data();
		prev_->next(popped_->next());
		size_--;
		delete popped_;
		return output_;
	}
}
/**
 * Inserts an element respecting a specific progression.
 * \param data data.
 */ 
template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
	Node* current_;
	int pos_;
	if (empty()) {
		push_front(data);
	} else {
		current_ = head;
		pos_ = 1;
		while (current_->next() != nullptr && data > current_->data()) {
			current_ = current_->next();
			pos_++;
		}
		if (data > current_->data()) {
			insert(data, pos_+1);
		} else {
			insert(data, pos_);
		}
	}
}
/**
 * Adds an element to the end of the list.
 */
template<typename T>
void LinkedList<T>::push_back(const T& data) {
	Node* input_ = new Node(data, nullptr);
	Node* prev_ = head;
	for(int i = 1; i < size_; i++) {
		prev_ = prev_->next();
	}
	prev_->next(input_);
}
/**
 * Removes the last element.
 */
template<typename T>
T LinkedList<T>::pop_back() {
	return pop(size_);
}
/**
 * Returns a reference to the element at the specified index.
 */
template<typename T>
T& LinkedList<T>::at(std::size_t index) {
    Node* current_;
    if (index > size_) {
        throw std::out_of_range("Index inválido");
    } else if (index == 1) {
  	    current_ = head;
  	    return current_->data();
  	} else {
  		current_ = head;
		for (int i = 0; i < index-1; i++) {
		    current_ = current_->next();
	    }
		return current_->data();
	}
}
/**
 * Checks if the list has a certain element, and if so, returns its index.
 * \return specified element index.
 */
template<typename T>
std::size_t LinkedList<T>::find(const T& data) const {
	Node* current_ = head;
	std::size_t index = size_+1;
	for (std::size_t i = 1; i < size_+1; i++) {
		if (current_->data() == data) {
			index = i;
			break;
		} else if (i != size_) {
			current_ = current_->next();
		}
	}
	return index;
}
/**
 * Removes an element by its content.
 * \param data data.
 */
template<typename T>
void LinkedList<T>::remove(const T& data) {
	std::size_t test_ = find(data);
	if (test_ != size_+1) {
		pop(test_);
	}
}
/**
 * Checks if the list contains a certain element by its content.
 * \return boolean
 */
template<typename T>
bool LinkedList<T>::contains(const T& data) const {
	return find(data) != size()+1;
}
/**
 * Returns the list current size.
 */
template<typename T>
std::size_t LinkedList<T>::size() const {
	return size_;
}
}  // namespace structures

#endif