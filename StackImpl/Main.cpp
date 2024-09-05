#include <iostream>
#include <string>

#include "ArrayStack.hpp"
#include "Wrapper.hpp"

bool check_sum(int a, int b, int sum);
bool check_sum_2(int a, int b, int sum);

int tests[] = {0,1,-1,INT_MAX, INT_MIN, -2000000000, 1000000000, 2000000000};

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
	if (a > 0 && b > 0) 
		return (sum >= 0) && (sum - b == a);
	if (a < 0 && b < 0) 
		return (sum < 0) && (sum - b == a);

	return (a + b == sum);
}

bool check_sum_2(int a, int b, int sum)
{
	if (((b > 0) && (a > (INT_MAX - b))) ||
		((b < 0) && (a < (INT_MIN - b)))) {
		return false;
	}
	return (a + b == sum);
}