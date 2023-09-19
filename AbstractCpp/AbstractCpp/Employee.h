#pragma once

#include "Person.h"

class Employee : Person
{

	std::string job;

public:

	Employee(const char* name, int age, const char* job);

	virtual void Do() override; // переопределяем метод из родителя 'Person'

};

