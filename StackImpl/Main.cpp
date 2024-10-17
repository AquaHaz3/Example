#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stack>
#include <cmath>
#include <algorithm>

#include "CombinedStack.h"
#include "DynamicStack.h"
#include "ArrayStack.hpp"
#include "ListStack.h"
#include "Wrapper.hpp"
#include "Sorts.h"
#include "tasks/Expressions.h"

template<typename T>
auto get_subsequence(std::vector<T> vec, int length) 
{
	if (length > vec.size()) {
		return vec.end();
	}
	if (length == vec.size()) {
		return vec.begin();
	}

	for (int i = 0; i < vec.size(); i++) {
		
	}
}

struct Vec2 
{
	double x;
	double y;

	Vec2 operator-(const Vec2& o) { return Vec2{ x - o.x, y - o.y }; }
	Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; }

	inline double sqr_len() { 
		return x * x + y * y;
	}
};

inline double polarity(Vec2 a, Vec2 b) {
	return a.x * b.y - a.y * b.x;
}

std::stack<Vec2> convex_hull(std::vector<Vec2>& points) 
{
	Vec2* lowest = &points[0];
	for (auto point : points) {
		if (point.y < lowest->y ||
			(point.y == lowest->y && point.x < lowest->x)
			) {
			lowest = &point;
		}
	}

	for (auto& p : points) {
		p.x -= lowest->x;
		p.y -= lowest->y;
	}

	sort(points.begin(), points.end(), [&](Vec2& a, Vec2& b)
	{
		return polarity(a,b) > 0 || polarity(a,b) == 0 && a.sqr_len() < b.sqr_len();
	});

	std::stack<Vec2> s;
	Vec2* behind_top = &points[0];
	for (int i = 0; i < points.size(); i++) {
		auto p = points[i];
		while (s.size() >= 2 && polarity((p - s.top()), *behind_top - s.top()) <= 0)
		{
			s.pop();
		}
		if (!s.empty()) behind_top = &s.top();
		s.push(p);
	}

	for (auto& p : points) {
		p.x += lowest->x;
		p.y += lowest->y;
	}

	return s;
}

int main()
{

}

