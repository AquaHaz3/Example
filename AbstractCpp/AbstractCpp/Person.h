#pragma once

#include <string>

class Person
{

	int age;
	std::string name;

public:

	Person(const char* name, int age);

	virtual void Do() = 0; /* чистый вирутальный метод */

};

