#include <iostream>
#include <string>

#include "ArrayStack.hpp"
#include <stack>

bool check_sum(int a, int b, int sum);

int main() 
{
	ArrayStack<int> s = ArrayStack<int>(2);

	s.push(1);
	s.push(2);
	s.push(3); // expand capacity
	s.push(4);
	s.push(5);

	while(!s.empty()) 
	{
		std::cout << s.top() << std::endl;
		s.pop();
	};
}

/*
	Not completed yet! just beta test (maybe don't work)
*/
bool check_sum(int a, int b, int sum)
{
	if (b > 0 && sum > 0) return (sum - b == a);
	if (a > 0 && sum > 0) return (sum - a == b);
	return (sum > 0) && (sum - a == b);
}
