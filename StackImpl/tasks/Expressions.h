#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

class Expressions
{

public:

	Expressions();

	std::string::iterator check_bracket_expr(
		const std::string::iterator& begin, const std::string::iterator& end);

private:

	void register_bracket_pair(char open, char close);

	std::set<char> open_brackets;

	/* map: closed_brackets -> open_brackets */
	std::map<char, char> bracket_map;

};