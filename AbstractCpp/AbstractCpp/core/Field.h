#pragma once

#include "Ring.h"

template <typename T>
class Field : virtual public Ring<T>
{

public:

	Field() : Ring<T>() { };

	virtual T getInverseByPlus(T element) = 0;
	virtual T getInverseByMultiply(T element) = 0;

	virtual T getZero() = 0;
	virtual T getOne() = 0;

	virtual T getSum(T a, T b) = 0;
	virtual T getMultiply(T a, T b) = 0;

private:

};

