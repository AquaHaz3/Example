#include <iostream>
#include <string>

#include "ArrayStack.hpp"
#include "Wrap.hpp"

bool check_sum(int a, int b, int sum);

int main() 
{
	ArrayStack<Wrapper> s = ArrayStack<Wrapper>(2);

	s.push(Wrapper(1));
	s.push(Wrapper(2));
	s.push(Wrapper(3)); // expand capacity
	s.push(Wrapper(4));
	s.push(Wrapper(5));

	while(!s.empty()) 
	{
		std::cout << s.top().uuid << std::endl;
		s.pop();
	};

}

#include <limits.h>

bool check_sum(int a, int b, int sum)
{
	if (((b > 0) && (a > (INT_MAX - b))) ||
		((b < 0) && (a < (INT_MIN - b)))) {
		return false;
	}
	return (a + b == sum);
}