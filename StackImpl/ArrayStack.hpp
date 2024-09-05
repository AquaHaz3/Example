#pragma once

#include <memory>

template <typename T>

class ArrayStack
{

	T* data = nullptr;
	size_t count = 0;
	size_t capacity = 0;

public:

	ArrayStack(int capacity = 5000) 
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

	~ArrayStack() 
	{
		if (data != nullptr) {
			delete[] data;
		}
	}

private:

	void expand_capacity();

};

template<typename T>
inline void ArrayStack<T>::push(const T& value)
{
	if (count >= capacity) {
		expand_capacity();
	}
	this->data[count] = value;
	count++;
}

template<typename T>
inline void ArrayStack<T>::push(T&& value)
{
	if (count >= capacity) {
		expand_capacity();
	}
	this->data[count] = std::move(value);
	count++;
}

template<typename T>
inline void ArrayStack<T>::pop() noexcept
{
	if (count == 0) return;
	count--;
}

template<typename T>
inline T& ArrayStack<T>::top()
{
	if (count == 0) {
		throw std::exception("Empty stack");
	}
	return data[count - 1];
}

template<typename T>
inline const T& ArrayStack<T>::top() const
{
	if (count == 0) {
		throw std::exception("Empty stack");
	}
	return data[count - 1];
};

template<typename T>
inline void ArrayStack<T>::expand_capacity()
{
	capacity = capacity * 2;
	T* temp = new T[capacity];
	std::copy(&data[0], &data[count], &temp[0]);
	delete[] data;
	data = temp;
}
