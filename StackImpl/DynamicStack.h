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
	void pop();

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

private:

	void expand_capacity();

};

template<typename T>
inline void stack_array<T>::push(const T& value)
{
	if (count >= capacity) {
		expand_capacity();
	}
	this->data[count] = value;
	count++;
}

template<typename T>
inline void stack_array<T>::push(T&& value)
{
	if (count >= capacity) {
		expand_capacity();
	}
	this->data[count] = std::move(value);
	count++;
}

template<typename T>
inline void stack_array<T>::pop()
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

template<typename T>
inline void stack_array<T>::expand_capacity()
{
	capacity = capacity * 2;
	T* temp = new T[capacity];
	std::move(&data[0], &data[count], &temp[0]);
	delete[] data;
	data = temp;
}
