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

int main()
{

	std::string expr = "(()()(())[]{(<>)})";
	int pos = 0;
	Expressions util = Expressions();
	util.semi_valid_expr(expr, pos);

}

template <typename T>
bool get_frequent_element(std::vector<T> vec) 
{
	std::stack<T> s;
    for (auto el : vec) {
        if (s.size() == 0) {
            s.push(el)
        }
        else {
            if (el == s.top()) {
                s.push(el)
            }
            else {
                s.pop()
            }
        }
    }

    if (s.size() == 0) {
        return false;
    }

    int count = 0;
    return (count(arr, s.top()) > arr.size / 2)
}
