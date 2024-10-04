#include "Expressions.h"
#include <stack>
#include <set>
#include <unordered_map>

Expressions::Expressions()
{
	open_brackets = std::vector<char>();
	close_brackets = std::vector<char>();
	register_bracket_pair('(', ')');
	register_bracket_pair('[', ']');
	register_bracket_pair('{', '}');
	register_bracket_pair('<', '>');
}

inline int Expressions::get_open_bracket_id(char bracket)
{
	for (int i = 0; i < open_brackets.size(); i++) {
		if (open_brackets[i] == bracket) {
			return i;
		}
	}
	return -1;
}

inline int Expressions::get_close_bracket_id(char close_bracket)
{
	for (int i = 0; i < close_brackets.size(); i++) {
		if (close_bracket == close_brackets[i]) {
			return i;
		}
	}
	return -1;
}

bool Expressions::semi_valid_expr(std::string expr, int& flipPosition)
{
	std::stack<char> s;
	int top_edge = 0;

	int last_type = -1;
	int last_type_count = 0;

	bool is_first_attempt = true;

	for (int i = 0; i < expr.size(); i++) 
	{
		int open_bracket_id = get_open_bracket_id(expr[i]);
		if (open_bracket_id != -1) 
		{
			if (last_type != open_bracket_id) {
				last_type_count = 0;
			}
			last_type = open_bracket_id;
			last_type_count++;
			s.push(expr[i]);
			continue;
		}
		int close_bracket_id = get_close_bracket_id(expr[i]);
		if (close_bracket_id != -1) 
		{

			if (s.top() != close_brackets[close_bracket_id]) 
			{
				if (last_type_count == 2 && is_first_attempt) 
				{
					flipPosition = (i - 2) + (get_open_bracket_id(s.top()) != -1);
					is_first_attempt = false;
				}
				return false;
			}
			else {
				s.pop();
				last_type_count--;
				if (s.size() == 0) {
					top_edge = i;
				}
			};

			if (last_type != close_bracket_id) {
				last_type_count = 0;
			}
			last_type = close_bracket_id;
			last_type_count++;
		}
	}

	if (s.size() == 2 && is_first_attempt) {
		char t = s.top();
		s.pop();
		if (t == s.top()) {
			flipPosition = top_edge + (get_open_bracket_id(t) != -1);
			return true;
		}
		return false;
	}

	if (s.size() > 0) {
		return false;
	}

	return true;

}

void Expressions::register_bracket_pair(char open, char close)
{
	open_brackets.push_back(open);
	close_brackets.push_back(close);
}
