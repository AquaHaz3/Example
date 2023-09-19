#include "Employee.h"
#include <iostream>

Employee::Employee(const char* name, int age, const char* job)
	: Person(name, age) // вызываем конструктор у Персоны
{
	this->job = std::string(job);
}

void Employee::Do()
{
	std::cout << "I'm work as " << job << "!" << std::endl;
}
