#pragma once

#include <memory>
#include <exception>
#include <cmath>
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

	} *head = nullptr;

	chunk_node* current_chunk = nullptr;

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
		clear();
	}

	stack_combined(stack_combined&& c) noexcept
	{
		count = c.count;
		policy = c.policy;
		head = c.head;
		current_chunk = c.current_chunk;
		c.head = nullptr;
		c.current_chunk = nullptr;
	};

	stack_combined(const stack_combined& c) noexcept
	{
		count = c.count;
		policy = c.policy;

		if (c.head == 0) 
			return;
	
		auto node = new chunk_node(c.head->capacity);
		auto cnode = c.head;
		head = node;
		head->count = c.head->count;
		if (c.head == c.current_chunk) current_chunk = head;
		std::copy(&c.head->data[0], &c.head->data[c.head->capacity], &head->data[0]);
		cnode = cnode->next;

		
		while (cnode != nullptr) {
			node->next = new chunk_node(cnode->capacity);
			node->next->count = cnode->count;
			if (cnode->capacity > 0) {
				std::copy(&cnode->data[0], &cnode->data[c.head->capacity], &node->next->data[0]);
			}
			if (cnode == c.current_chunk) {
				current_chunk = node->next;
			}
			cnode = cnode->next;
			node = node->next;
		}
	};

	stack_combined& operator=(const stack_combined& c) noexcept 
	{
		clear();
		count = c.count;
		policy = c.policy;

		if (c.head == 0) return;

		auto node = new chunk_node(c.head->capacity);
		auto cnode = c.head;
		head = node;
		head->count = c.head->count;
		if (c.head == c.current_chunk) current_chunk = head;
		std::copy(&c.head->data[0], &c.head->data[c.head->capacity], &head->data[0]);
		cnode = cnode->next;

		while (cnode != nullptr) {
			node->next = new chunk_node(cnode->capacity);
			node->next->count = cnode->count;
			if (cnode->capacity > 0) {
				std::copy(&cnode->data[0], &cnode->data[c.head->capacity], &node->next->data[0]);
			}
			if (cnode == c.current_chunk) {
				current_chunk = node->next;
			}
			cnode = cnode->next;
			node = node->next;
		}
		return *this;
	};

	stack_combined& operator=(stack_combined&& c) noexcept 
	{
		clear();
		count = c.count;
		policy = c.policy;
		head = c.head;
		current_chunk = c.current_chunk;
		c.head = nullptr;
		c.current_chunk = nullptr;
		return *this;
	};

private:

	void clear() {
		chunk_node* node = head;
		while (node != nullptr) {
			head = head->next;
			delete node;
			node = head;
		}
	}
	void expand_capacity();
	size_t get_next_capacity(size_t capacity);

};

template<typename T>
inline void stack_combined<T>::push(const T& value)
{
	if (current_chunk) {
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
	if (current_chunk->count == 0) {
		return current_chunk->next->data[current_chunk->next->count - 1];
	}
	return current_chunk->data[current_chunk->count - 1];
};

template<typename T>
inline size_t stack_combined<T>::get_next_capacity(size_t capacity)
{
	using enum chunk_size_policy;
	switch (policy)
	{
	case CONST: return capacity;
	case LINEAR: return capacity + 16;
	case EXP: return capacity * 2;
	case QUAD: return (int)(std::pow((std::sqrt(capacity)+1),2))
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
