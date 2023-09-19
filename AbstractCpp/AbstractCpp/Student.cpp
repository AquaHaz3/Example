#include "Student.h"
#include <iostream>

Student::Student(const char* name, int age, const char* university)
	: Person(name, age) // вызываем конструктор у Персоны
{
	this->university = std::string(university);
}

void Student::Do()
{
	std::cout << "I'm a student and I study at " << university << "!" << std::endl;
}
