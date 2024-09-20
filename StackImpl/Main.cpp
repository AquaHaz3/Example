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

	
	return 0;

}

bool check_sum_is_zero(const std::vector<int>& arr) 
{
	stack_array positive = stack_array<int>(arr.size());
	stack_array negative = stack_array<int>(arr.size());

	for (int num : arr) {
		if (num >= 0) positive.push(num);
		else negative.push(num);
	}

	int sum = 0;

	while (positive.size() > 0 || negative.size() > 0) {
		if (sum < 0) {
			if (positive.size() == 0) return false;
			sum += positive.top();
			positive.pop();
		}
		else {
			if (negative.empty()) return (sum == 0);
			sum += negative.top();
			negative.pop();
		}
	}

	return false;
} 