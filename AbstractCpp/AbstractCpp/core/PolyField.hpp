#pragma once

#include "PolyRing.hpp"
#include "Field.h"

template <typename T>
class PolyField : public PolyRing<T>, public Field<Polynom<T>*>
{

public:

	PolyField() {};

	virtual Polynom<T>* getInverseByPlus(Polynom<T>* element) = 0;
	virtual Polynom<T>* getInverseByMultiply(Polynom<T>* element) = 0;

	virtual Polynom<T>* getZero() = 0;
	virtual Polynom<T>* getOne() = 0;

	virtual Polynom<T>* getSum(Polynom<T>* a, Polynom<T>* b) = 0;
	virtual Polynom<T>* getMultiply(Polynom<T>* a, Polynom<T>* b) = 0;

};
