#pragma once

#include <memory>
#include <stdexcept>

template <typename T>

class stack_array
{

	T* data = nullptr;
	size_t count = 0;
	size_t capacity = 0;

public:

	stack_array(int capacity = 5000) 
	{
		this->capacity = capacity;
		data = new T[capacity];
	}

	void push(const T& value);
	void push(T&& value);
	T& top();
	const T& top() const;
	void pop() noexcept;

	bool empty() noexcept {
		return (count == 0);
	}

	size_t size() noexcept {
		return count;
	}

	~stack_array() 
	{
		if (data != nullptr) {
			delete[] data;
		}
	}

	stack_array(stack_array&& c) noexcept
	{
		data = c.data;
		count = c.count;
		capacity = c.capacity;
		c.data = nullptr;
	};

	stack_array(const stack_array& c) noexcept
	{
		data = new T[c.capacity];
		std::copy(&c.data[0], &c.data[c.capacity], &data[0]);
		count = c.count;
		capacity = c.capacity;
	};

	stack_array& operator=(const stack_array& c) noexcept {
		if (data) delete[] data;
		data = new T[c.capacity];
		std::copy(&c.data[0], &c.data[c.capacity], &data[0]);
		count = c.count;
		capacity = c.capacity;
		return *this;
	};

	stack_array& operator=(stack_array&& c) noexcept {
		if (data) delete[] data;
		data = c.data;
		count = c.count;
		capacity = c.capacity;
		c.data = nullptr;
		return *this;
	};

};

template<typename T>
inline void stack_array<T>::push(const T& value)
{
	if (count >= capacity) {
		throw std::overflow_error("Stack overflow");
	}
	this->data[count] = value;
	count++;
}

template<typename T>
inline void stack_array<T>::push(T&& value)
{
	if (count >= capacity) {
		throw std::overflow_error("Stack overflow");
	}
	this->data[count] = std::move(value);
	count++;
}

template<typename T>
inline void stack_array<T>::pop() noexcept
{
	if (count == 0) {
		throw std::underflow_error("Empty stack");
	}
	count--;
}

template<typename T>
inline T& stack_array<T>::top()
{
	if (count == 0) {
		throw std::length_error("Empty stack");
	}
	return data[count - 1];
}

template<typename T>
inline const T& stack_array<T>::top() const
{
	if (count == 0) {
		throw std::length_error("Empty stack");
	}
	return data[count - 1];
};