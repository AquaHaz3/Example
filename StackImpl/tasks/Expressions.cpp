#include "Expressions.h"
#include <stack>
#include <set>

Expressions::Expressions()
{
	open_brackets = std::set<char>();
	bracket_map = std::map<char, char>();
	register_bracket_pair('(', ')');
	register_bracket_pair('[', ']');
	register_bracket_pair('{', '}');
	register_bracket_pair('<', '>');
}

std::string::iterator Expressions::check_bracket_expr(
	const std::string::iterator& begin, const std::string::iterator& end
)
{
	auto it = begin;
	std::stack<std::string::iterator> positions;
	while (it != end)
	{
		if (open_brackets.contains(it[0])) {
			positions.push(it);
			it++;
			continue;
		}

		auto close = bracket_map.find(it[0]);
		if (close != bracket_map.end()) {
			if (*positions.top() != close->second) {
				return it;
			}
			else {
				positions.pop();
			};
		}
		it++;
	}

	if (positions.size() > 0) {
		std::string::iterator err_pos;
		err_pos = positions.top();
		return err_pos;
	}

	return end;
}

void Expressions::register_bracket_pair(char open, char close)
{
	open_brackets.emplace(open);
	bracket_map.emplace(close, open);
}
