
#include <vector>
#include <iostream>

#include "Employee.h"
#include "Student.h"
#include "Person.h"


int main()
{
	std::vector<Person*> persons = std::vector<Person*>();

	persons.push_back((Person*) new Employee("John", 28, "Policeman"));
	persons.push_back((Person*) new Employee("Mike", 30, "Builder"));
	persons.push_back((Person*) new Student("Andrew", 21, "Sydney"));
	persons.push_back((Person*) new Student("Kate", 22, "Cambridge"));

	//persons.push_back((Person*) new Person("Chel", 20)); // ���� ������ �����������, �� VS ������ ��� ������ ������� 0 �����

	for (int i = 0; i < persons.size(); i++) {
		persons[i]->Do(); // �������� ����������� ����� 'Person', �� ��������� ����� �� ����������
	}

	for (int i = 0; i < persons.size(); i++) {
		if (persons[i] != nullptr) {
			delete persons[i]; // �������
		}
	}

}