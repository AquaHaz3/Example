#pragma once

#include <memory>
#include <exception>
#include <stdexcept>

enum class chunk_size_policy
{
	CONST,
	LINEAR,
	EXP,
	QUAD
};

template <typename T>

class stack_combined
{

	size_t count = 0;
	chunk_size_policy policy;

	struct chunk_node
	{
		T* data = nullptr;
		size_t capacity = 0;
		size_t count = 0;
		chunk_node* next = nullptr;

		chunk_node(int _capacity) {
			capacity = _capacity;
			if (capacity <= 0) capacity = 8;
			data = new T[capacity];
		}

		~chunk_node() {
			if (data) delete[] data;
		}

	} *head = 0;

	chunk_node* current_chunk = 0;

public:

	stack_combined(
		int capacity = 100,
		chunk_size_policy _policy = chunk_size_policy::CONST
	) : policy(_policy)
	{
		if (capacity != 0) {
			current_chunk = new chunk_node(capacity);
			head = current_chunk;
		}
	};

	void push(const T& value);
	void push(T&& value);
	T& top();
	const T& top() const;
	void pop();

	size_t size() noexcept {
		return count;
	}

	~stack_combined()
	{
		chunk_node* node = head;
		while (node != nullptr) {
			head = head->next;
			delete node;
			node = head;
		}
	}

private:

	void expand_capacity();
	size_t get_next_capacity(size_t capacity);

};

template<typename T>
inline void stack_combined<T>::push(const T& value)
{
	if (current_chunk == 0) {
		current_chunk = new chunk_node(8);
		head = current_chunk;
	}
	if (current_chunk->count >= current_chunk->capacity) {
		expand_capacity();
	}
	current_chunk->data[current_chunk->count] = value;
	count++;
	current_chunk->count++;
}

template<typename T>
inline void stack_combined<T>::push(T&& value)
{
	if (current_chunk == 0) {
		current_chunk = new chunk_node(8);
		head = current_chunk;
	}
	if (current_chunk->count >= current_chunk->capacity)
	{
		expand_capacity();
	}
	current_chunk->data[current_chunk->count] = std::move(value);
	count++;
	current_chunk->count++;
}

template<typename T>
inline void stack_combined<T>::pop()
{
	if (count == 0) {
		throw std::underflow_error("Empty stack");
	}
	if (current_chunk->count == 0) {
		if (current_chunk->next == 0) {
			throw std::underflow_error("Empty stack");
		}
		if (head->next == current_chunk) {
			delete head;
			head = current_chunk;
		}
		current_chunk = current_chunk->next;
	}
	current_chunk->count--;
	count--;
}

template<typename T>
inline T& stack_combined<T>::top()
{
	if (count == 0 || current_chunk == 0) {
		throw std::length_error("Empty stack");
	}
	if (current_chunk->count == 0) {
		return current_chunk->next->data[current_chunk->next->count - 1];
	}
	return current_chunk->data[current_chunk->count - 1];
}

template<typename T>
inline const T& stack_combined<T>::top() const
{
	if (count == 0 || current_chunk == 0) {
		throw std::length_error("Empty stack");
	}
	return current_chunk->data[current_chunk->count - 1];
};

template<typename T>
inline size_t stack_combined<T>::get_next_capacity(size_t capacity)
{
	static size_t i = 1;
	i++;
	using enum chunk_size_policy;
	switch (policy)
	{
	case CONST: return capacity;
	case LINEAR: return capacity + 16;
	case EXP: return capacity * 2;
	case QUAD: return i*i;
	default:
		return capacity;
	}
}

template<typename T>
inline void stack_combined<T>::expand_capacity()
{
	if (head->next == current_chunk) {
		current_chunk = head;
		return;
	}

	chunk_node* chunk = new chunk_node(
		get_next_capacity(current_chunk->capacity)
	);

	chunk->next = current_chunk;

	if (head == current_chunk) {
		head = chunk;
	}

	current_chunk = chunk;
}
