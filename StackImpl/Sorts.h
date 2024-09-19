#pragma once

#include "ArrayStack.hpp"
#include <algorithm>

template <typename type_stack>
void selection_sort(type_stack& stack)
{

	int s_size = stack.size();

	if (s_size == 0) return;

	type_stack buf(s_size);
	type_stack result(s_size);
	type_stack* effective = &stack;
	type_stack* buffer = &buf;

	auto max = stack.top();
	auto old_max = stack.top();
	bool selection = false;

	while (result.size() < s_size) {
		max = effective->top();
		while (effective->size() > 0)
		{
			auto _top = effective->top();
			if (selection && _top == old_max) {
				result.push(_top);
				effective->pop();
				selection = false;
				continue;
			}
			if (_top > max) {
				max = _top;
			}
			effective->pop();
			buffer->push(_top);
		}
		selection = true;
		std::swap<type_stack*>(effective, buffer);
		old_max = max;
	}

	while (stack.size() > 0) {
		stack.pop();
	}
	while (result.size() > 0) {
		stack.push(result.top());
		result.pop();
	}
}