#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

class Expressions
{

public:

	Expressions();

	//std::string::iterator check_bracket_expr(
	//	const std::string::iterator& begin, const std::string::iterator& end);

	bool semi_valid_expr(std::string expr, int& flipPosition);

private:

	void register_bracket_pair(char open, char close);
	
	inline int get_close_bracket_id(char close_bracket);
	inline int get_open_bracket_id(char bracket);

	std::vector<char> open_brackets;
	std::vector<char> close_brackets;

};