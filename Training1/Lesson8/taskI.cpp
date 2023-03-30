#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct Graph {
    std::vector<std::vector<int>> adj_list;
    std::vector<bool> visited;
    std::vector<int> descendants;

    Graph(std::vector<std::vector<int>> adj_list_);

    void dfs(int a, int& b);

    [[nodiscard]] auto GetDescendants() const->std::vector<int>;
};

namespace Family {

    std::map<std::string, int> family;
    std::vector<std::vector<int>> adj_list;
    int start = 0;
    void MakeFamily(int n);

} //namespace Family

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;

    Family::MakeFamily(n);
    auto graph = std::make_unique<Graph>(Family::adj_list);
    int c = 0;
    graph->dfs(Family::start, c);
    std::vector<int> const descendants = graph->GetDescendants();
    for (auto const& elem : Family::family) {
        std::cout << elem.first << ' ' << descendants[elem.second] << '\n';
    }
}

void Family::MakeFamily(int n)
{
    adj_list.resize(n);
    int idx = 0;
    std::vector<int> root(n);
    for (int i = 0; i < n - 1; ++i) {
        std::string son;
        std::string parent;
        std::cin >> son >> parent;
        int dest = 0;
        if (family.find(son) != family.end()) {
            dest = family[son];
        }
        else {
            dest = idx;
            family.emplace(son, idx++);
        }
        int src = 0;
        if (family.find(parent) != family.end()) {
            src = family[parent];
        }
        else {
            src = idx;
            family.emplace(parent, idx++);
        }
        adj_list[src].push_back(dest);
        root[dest]++;
    }
    start = std::find(root.begin(), root.end(), 0) - root.begin();
}

Graph::Graph(std::vector<std::vector<int>> adj_list_)
    : adj_list(std::move(adj_list_))
{
    size_t const size = adj_list.size();
    descendants.resize(size);
    visited.resize(size, false);
}

void Graph::dfs(int a, int& b)
{
    visited[a] = true;
    descendants[a] = ++b;
    for (auto it : adj_list[a]) {
        if (!visited[it]) {
            dfs(it, b);
        }
    }
    descendants[a] = b - descendants[a];
}

auto Graph::GetDescendants() const -> std::vector<int>
{
    return descendants;
}
