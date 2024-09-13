#include <iostream>
#include <string>
#include <vector>

#include "CombinedStack.h"
#include "Wrapper.hpp"

int tests[] = {0,1,-1,INT_MAX, INT_MIN, -2000000000, 1000000000, 2000000000, -1000000000, -1000, 1000 };

bool check_sum_is_zero(const std::vector<int>& arr);

int main() 
{

	//int a = INT_MIN;
	//int b = -8;
	//int c = a + b;
	//printf("%d", c);

	return 0;

	stack_combined<Wrapper> s 
		= stack_combined<Wrapper>(2, chunk_size_policy::EXP);

	s.push(Wrapper(1));
	s.push(Wrapper(2));
	s.push(Wrapper(3)); // expand capacity
	s.push(Wrapper(4));
	s.push(Wrapper(5));

	while(s.size() > 0) 
	{
		std::cout << s.top().uuid << std::endl;
		s.pop();
	};

	return 0;

}

/*
@return
1 - positive overflow, -1 negative overflow, 0 - no overflow
*/
int overflow_dir(int a, int b)
{
	int sum = a + b;
	if (a > 0 && b > 0 && sum < a) return 1;
	if (a < 0 && b < 0 && sum > a) return -1;
	return 0;
}

bool check_sum_is_zero(const std::vector<int>& arr) 
{
	int sum = 0;
	int cycles = 0;
	for (int num : arr) {
		cycles = cycles + overflow_dir(num, sum);
		sum = sum + num;
	}
	sum |= cycles;
	return (sum == 0);
} 