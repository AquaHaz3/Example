#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stack>
#include <cmath>

#include "CombinedStack.h"
#include "DynamicStack.h"
#include "ArrayStack.hpp"
#include "ListStack.h"
#include "Wrapper.hpp"
#include "Sorts.h"
#include "tasks/Expressions.h"

bool check_product(std::vector<int>& arr1, std::vector<int>& arr2);

int main()
{

	std::string expr = "(()()(())[]{(<>)})";
	Expressions util = Expressions();
	auto it = util.check_bracket_expr(expr.begin(), expr.end());
	if (it != expr.end()) {
		printf("%c", it[0]);
	}

	test_sort_random_order();
	test_sort_descend_order();

}

uint32_t multiplicative_inverse(uint32_t a)
{
	uint32_t x0 = (3 * a) ^ 2;
	uint32_t y = 1 - a * x0;
	uint32_t x1 = x0 * (1 + y);
	y *= y;
	uint32_t x2 = x1 * (1 + y);
	y *= y;
	uint32_t x3 = x2 * (1 + y);
	return x3;
}
bool check_product(std::vector<int>& arr1, std::vector<int>& arr2) 
{

	bool is_zero_found = false;
	int sign1 = 1;
	int sign2 = 1;
	int two1 = 0;
	int two2 = 0;

	for (int i = 0; i < arr1.size(); i++) {
		if (arr1[i] == 0) {
			is_zero_found = true;
			break;
		}
		if(arr1[i] < 0) {
			sign1 *= -1;
		}
		while((arr1[i] & 1) == 0) {
			two1++;
			arr1[i] = arr1[i] >> 1;
		}
	}

	for (int i = 0; i < arr2.size(); i++) {
		if (arr2[i] == 0) {
			return is_zero_found;
		}
		if (arr2[i] < 0) {
			sign2 *= -1;
		}
		while ((arr2[i] & 1) == 0) {
			two2++;
			arr2[i] = arr2[i] >> 1;
		}
	}

	if (two1 != two2) return false;
	if (sign1 != sign2) return false;
	if (is_zero_found) return false;
	
	
}