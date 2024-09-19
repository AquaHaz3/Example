#include <iostream>
#include <string>
#include <vector>

#include "CombinedStack.h"
#include "Wrapper.hpp"
#include "Sorts.h"

int tests[] = {0,1,-1,INT_MAX, INT_MIN, -2000000000, 1000000000, 2000000000, -1000000000, -1000, 1000 };

bool check_sum_is_zero(const std::vector<int>& arr);

int main() 
{

	stack_combined<int> s 
		= stack_combined<int>(9, chunk_size_policy::EXP);

	s.push(7);
	s.push(4);
	s.push(5);
	s.push(3);
	s.push(2);
	s.push(1);
	s.push(6);
	s.push(0);

	selection_sort<stack_combined<int>>(s);

	while(s.size() > 0) 
	{
		std::cout << s.top() << std::endl;
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
	if (a > 0 && b > 0 && sum < a && sum < b) return  1;
	if (a < 0 && b < 0 && sum > a && sum > b) return -1;
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
	return (sum == 0 && cycles == 0);
} 