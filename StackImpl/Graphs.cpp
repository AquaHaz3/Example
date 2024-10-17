#include "Graphs.h"

#include <algorithm>
#include <stack>

std::vector<int> Graphs::get_euler_path(std::vector<std::vector<int>> g)
{
    if (g.size() == 0) return {};
    
    auto it = std::find_if(g.begin(), g.end(), 
        [](auto& lst) { return lst.size() % 2 == 1; }
    );

    std::stack<int> s;

    s.push(it == end(g) ? 0 : (it - begin(g)));

    std::vector<int> path;
    while (s.size()) {
        auto u = s.top();
        if (g[u].size() == 0) {
            path.push_back(u);
            s.pop();
        }
        else {
            auto v = g[u].back();
            s.push(v);
            g[u].pop_back();
            std::iter_swap(std::find(begin(g[v]), end(g[v]), u), rbegin(g[v]));
            g[u].pop_back();
        }
    }

    if (std::all_of(begin(g), end(g), [](auto& lst) {return lst.size() == 0; })) {
        return path;
    }

    return {};
}
