#include "Person.h"

Person::Person(const char* name, int age)
{
	this->name = std::string(name);
	this->age = age;
}
