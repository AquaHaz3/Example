#pragma once

#include "Person.h"

class Student : Person
{

	std::string university;

public:

	Student(const char* name, int age, const char* university);

	virtual void Do() override; // переопределяем метод из родителя 'Person'

};

