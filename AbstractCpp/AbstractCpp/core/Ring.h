#pragma once
#include "MathSet.hpp"

template <typename T>
class Ring : public MathSet<T>
{
public:

	Ring() : MathSet<T>() {}

	virtual T getInverseByPlus(T element) = 0;

	virtual T getZero() = 0;
	virtual T getOne() = 0;

	virtual T getSum(T a, T b) = 0;
	virtual T getMultiply(T a, T b) = 0;

	std::set<T>& getElements() {
		return this->elements;
	}

protected:

	T _one;
	T _zero;

};

