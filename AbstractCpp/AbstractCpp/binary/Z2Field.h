#pragma once

#include "CoreAPI.h"
#include <stdint.h>
#include <iostream>

#define _qword_high_bit 0b1000000000000000000000000000000000000000000000000000000000000000

class Z2Field : public Field<uint8_t> 
{
public:

	Z2Field() : Field<uint8_t>() {
		_one = 1;
		_zero = 0;
		insert(0);
		insert(1);
	};

	virtual uint8_t getInverseByPlus(uint8_t element) override;
	virtual uint8_t getInverseByMultiply(uint8_t element) override;

	virtual uint8_t getZero() override;
	virtual uint8_t getOne() override;

	virtual uint8_t getSum(uint8_t a, uint8_t b) override;
	virtual uint8_t getMultiply(uint8_t a, uint8_t b) override;

};

class Z2Polynom : public Polynom<uint8_t> 
{

public:

	Z2Polynom() {
		data = 0;
		size = (int)PolynomDegree::DEG_ZERO;
	}

	Z2Polynom(uint8_t alpha)
	{
		data = alpha & 1;
		size = (int)PolynomDegree::DEG_ALPHA;
	}

	Z2Polynom(__int64 raw, bool isRaw)
	{
		data = raw;
		size = 0;
		if (data == 0) size = (int)PolynomDegree::DEG_ZERO;
		else if (data == 1) size = (int)PolynomDegree::DEG_ALPHA;
		else {
			for (int i = 1; i < 8; i++) {
				if (((data << i) & _qword_high_bit) > 0)
				{
					size = 7 - i;
					break;
				}
			}
		}
	}

	~Z2Polynom() {
		std::cout << "[Arena] free Z2 polynom" << '\n';
	}

	virtual void place(uint8_t alpha, int pow) override {
		if (pow > 63 && pow < -1) {
			throw std::exception("[ polynom::Z2[x] ] overflow power (or < 0)");
		}
		__int64 bit = alpha & 1;
		data = (bit << pow) & data;
		size = std::max(size, pow);
	};

	virtual int deg() override {
		return size;
	}

	virtual Z2Polynom* operator+(const Polynom<uint8_t>* a) override
	{
		Z2Polynom* ref = (Z2Polynom*) a;
		return new Z2Polynom(ref->data ^ this->data, true);
	}

	__int64 data;

private:

	int size;

};

class Z2PolyField : PolyField<uint8_t> 
{

public:

	Z2PolyField() {
		_zero = new Z2Polynom(32, 0);
		_one = new Z2Polynom(32, 1);
	};

	virtual Z2Polynom* getZero() {
		return (Z2Polynom*)_zero;
	};

	virtual Z2Polynom* getOne() {
		return (Z2Polynom*) _one;
	};

	virtual Z2Polynom* getSum(Z2Polynom* a, Z2Polynom* b) 
	{
		return a->operator+(b);
	}

	virtual Z2Polynom* getMultiply(Z2Polynom* a, Z2Polynom* b)
	{
		
	}

	virtual Z2Polynom* getInverseByPlus(Z2Polynom* element)
	{
		
	}

	virtual Z2Polynom* getInverseByMultiply(Z2Polynom* element)
	{

	}

private:



};