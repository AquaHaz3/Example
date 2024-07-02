#pragma once

#include <set>

template <typename T>
class MathSet {

public:

	MathSet() {
		std::set<T> elements = std::set<T>();
	}

	void insert(T element) {
		elements.insert(element);
	}

	bool contains(T element) {
		return (elements.count(element) > 0);
	}

	std::set<T> elements;

};