#pragma once

#include <vector>
#include <ostream>
#include "Ring.h"

template <typename A>
class Polynom
{

public:

	Polynom() {}
	~Polynom() {};

	virtual void place(A alpha, int pow) = 0;
	virtual int deg() = 0;

	virtual Polynom* operator+(const Polynom* a) = 0;

	virtual std::ostream& operator<<(std::ostream& os) {os << "(abstract_polynom)"; return os; };

};

enum class PolynomDegree {

	DEG_ZERO = -1,
	DEG_ALPHA = 0

};

template <typename T>
class PolyRing : virtual public Ring<Polynom<T>*> {

public:

	PolyRing() {};

	~PolyRing() 
	{
		for (auto e : this->getElements()) 
		{
			delete e;
		}
	}

	virtual Polynom<T>* getInverseByPlus(Polynom<T>* element) = 0;

	virtual Polynom<T>* getZero() = 0;
	virtual Polynom<T>* getOne() = 0;

	virtual Polynom<T>* getSum(Polynom<T>* a, Polynom<T>* b) = 0;
	virtual Polynom<T>* getMultiply(Polynom<T>* a, Polynom<T>* b) = 0;

};