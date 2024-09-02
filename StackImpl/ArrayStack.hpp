#pragma once

#include <memory>

template <typename T>

class ArrayStack
{

public:

	ArrayStack(int capacity = 5000) 
	{
		this->capacity = capacity;
		data = new T[capacity];
	}

	void push(const T& value) 
	{
		if (count >= capacity) {
			capacity = capacity * 2;
			T* temp = new T[capacity];
			std::copy(&data[0], &data[capacity], &temp[0]); // copy data from data[] -> temp[]
			delete[] data;
			data = temp;
		}
		this->data[count] = value;
		count++;
	}

	void push(T&& value) 
	{
		if (count >= capacity) {
			capacity = capacity * 2;
			T* temp = new T[capacity];
			std::copy(&data[0], &data[count], &temp[0]);
			delete[] data;
			data = temp;
		}
		this->data[count] = value;
		count++;
	}

	void pop() noexcept
	{
		if (count == 0) return;
		count--;
	};

	const T& const top()
	{
		if (count == 0) {
			throw std::exception("Empty stack");
		}
		return data[count-1];
	};

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

	T* data;
	size_t count = 0;
	size_t capacity = 0;

};
