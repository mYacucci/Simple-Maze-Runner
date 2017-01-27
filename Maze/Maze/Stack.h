#include <cstdlib>

using namespace std;

#ifndef _STACK_H
#define _STACK_H

template <typename T>class Stack {

private:
	T* stack;		// pointer to the container
	int index;		// index number of the next avalable slot
	int capacity;	// number of slots in the container

public:

	/**
	 * Creates a new Stack with a user specifed capacity. If the user fails
	 * to specify a capacity, then it defaults to capacity of 10
	 *
	 * parameter capacity specifies the number of slots used for the stack
	 */
	Stack(int capacity = 10) : capacity(capacity) {

		stack = new T[capacity];
		index = 0;
	}

	/**
	 * Returns the container memory back to the OS
	 */
	~Stack();

	/**
	 * determines whether the container is empty
	 *
	 * returns true if the container is empty else false
	 */
	bool isEmpty();

	/**
	 * used to determine if the container is full
	 *
	 * returns true if the container is full else false
	 */
	bool isFull();

	/**
	 * puts a value on top of the stack
	 *
	 * param is the value to be places on top of the stack
	 */
	void push(T value);

	/**
	 * returns a copy of the value located at the top of the stack
	 *
	 * returns a copy of the value located at the top of the stack
	 */
	T top();

	/**
	 * removes the value from the top of the stack
	 */
	void pop();

};

template <typename T>Stack<T>::~Stack() { delete[] stack; }

template <typename T>bool Stack<T>::isEmpty() { 
		return (index == 0)? true : false;
	}

template <typename T>bool Stack<T>::isFull() {
		return (index == capacity) ? true : false;
	}

template <typename T>void Stack<T>::push(T value) { stack[index++] = value;}

template <typename T>T Stack<T>::top() { return stack[index-1]; }

template <typename T>void Stack<T>::pop() { --index;}

#endif