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

template <typename type_stack>
void move_ascending_top(type_stack& source, type_stack& dest)
{
	while (source.size() > 0) {
		dest.push(source.top());
		source.pop();
		if (source.size() == 0) break;
		if (source.top() < dest.top()) {
			break;
		}
	}
}

template <typename type_stack>
void merge_ordered_stacks(type_stack& src1, type_stack& src2, type_stack& dest)
{
	while (src1.size() > 0 && src2.size() > 0) {
		if (src1.top() > src2.top()) {
			dest.push(src1.top());
			src1.pop();
		}
		else {
			dest.push(src2.top());
			src2.pop();
		}
	}

	auto left = (src1.size() == 0) ? &src2 : &src1;
	
	while (left->size() > 0) {
		dest.push(std::move(left->top()));
		left->pop();
	}
}

template <typename type_stack>
void merge_sort(type_stack& source)
{
	type_stack buffer0 = type_stack();
	type_stack buffer1 = type_stack();
	type_stack buffer2 = type_stack();

	auto src = &source;
	auto buf0 = &buffer0;
	auto buf1 = &buffer1;
	auto dest = &buffer2;

	int steps = 2;

	while (steps > 1 || src != &source)
	{
		steps = 0;
		while (src->size() > 0) {
			move_ascending_top<type_stack>(*src, *buf0);
			move_ascending_top<type_stack>(*src, *buf1);
			merge_ordered_stacks<type_stack>(*buf0, *buf1, *dest);
			steps++;
		}
		std::swap(src, dest);
	}
}

template <typename type_stack>
void merge_sort_static(type_stack& source, int size)
{
	type_stack buffer0 = type_stack(size);
	type_stack buffer1 = type_stack(size);
	type_stack buffer2 = type_stack(size);

	auto src = &source;
	auto buf0 = &buffer0;
	auto buf1 = &buffer1;
	auto dest = &buffer2;

	int steps = 2;

	while (steps > 1 || dest == &source)
	{
		steps = 0;
		while (src->size() > 0) {
			move_ascending_top<type_stack>(*src, *buf0);
			move_ascending_top<type_stack>(*src, *buf1);
			merge_ordered_stacks<type_stack>(*buf0, *buf1, *dest);
			steps++;
		}
		std::swap(src, dest);
	}
}

#include <chrono>

typedef std::mt19937 rng_type;

int tests[] = { 0,1,-1,INT_MAX, INT_MIN, -2000000000, 1000000000, 2000000000, -1000000000, -1000, 1000 };
rng_type rng;

#define TEST_TIME(code) {\
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(); \
{code;}; \
std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); \
std::cout << "dt(ms) = " \
<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() \
<< "[ms]" \
<< std::endl; \
}

void test_sort_random_order() 
{
	printf("test random\n");

	auto time_now = std::chrono::steady_clock::now();
	rng_type::result_type const seedval = time_now.time_since_epoch().count();
	rng.seed(seedval);

	auto s0 = stack_array<int>(50000);
	auto s1 = stack_darray<int>();
	auto s2 = stack_list<int>();
	auto s3 = stack_combined<int>();
	auto s4 = std::stack<int>();

	for (int i = 0; i < 50000; i++) {
		int r = (rng() & 0x7fffffff); //i; // 50000 - i
		s0.push(r);
		s1.push(r);
		s2.push(r);
		s3.push(r);
		s4.push(r);
	}

	TEST_TIME(merge_sort_static(s0, 50000));
	TEST_TIME(merge_sort(s1));
	TEST_TIME(merge_sort(s2));
	TEST_TIME(merge_sort(s3));
	TEST_TIME(merge_sort(s4));

	printf("\n\n");

	for (int i = 0; i < 3; i++) {
		printf("%d\t%d\t%d\t%d\t%d\n", s0.top(), s1.top(), s2.top(), s3.top(), s4.top());
		s0.pop();
		s1.pop();
		s2.pop();
		s3.pop();
		s4.pop();
	}

	printf("\n");
}

void test_sort_descend_order()
{

	printf("test 5 4 3 2 1 ...\n");
		
	auto time_now = std::chrono::steady_clock::now();
	rng_type::result_type const seedval = time_now.time_since_epoch().count();
	rng.seed(seedval);

	auto s0 = stack_array<int>(50000);
	auto s1 = stack_darray<int>();
	auto s2 = stack_list<int>();
	auto s3 = stack_combined<int>();
	auto s4 = std::stack<int>();

	for (int i = 0; i < 50000; i++) {
		int r = 50000 - i; //i; // 50000 - i
		s0.push(r);
		s1.push(r);
		s2.push(r);
		s3.push(r);
		s4.push(r);
	}

	TEST_TIME(merge_sort_static(s0, 50000));
	TEST_TIME(merge_sort(s1));
	TEST_TIME(merge_sort(s2));
	TEST_TIME(merge_sort(s3));
	TEST_TIME(merge_sort(s4));

	printf("\n\n");

	for (int i = 0; i < 3; i++) {
		printf("%d\t%d\t%d\t%d\t%d\n", s0.top(), s1.top(), s2.top(), s3.top(), s4.top());
		s0.pop();
		s1.pop();
		s2.pop();
		s3.pop();
		s4.pop();
	}

	printf("\n");
}