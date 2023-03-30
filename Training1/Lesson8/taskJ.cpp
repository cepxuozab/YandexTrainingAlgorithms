#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>
struct Graph {
    std::vector<std::vector<int>> adj_list;

    Graph(std::vector<std::vector<int>> adj_list_);

    [[nodiscard]] auto bfs(int start) const -> std::vector<int>;
};

namespace Family {

std::map<std::string, int> family;
std::vector<std::vector<int>> adj_list;
int start = 0;
void MakeFamily(int n);

} //namespace Family

auto main() -> int
{
    int n;
    std::cin >> n;

    Family::MakeFamily(n);
    auto graph = std::make_unique<Graph>(Family::adj_list);
    std::vector<int> const counts = graph->bfs(Family::start);
    for (auto const& elem : Family::family) {
        std::cout << elem.first << ' ' << counts[elem.second] << '\n';
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
        } else {
            dest = idx;
            family.emplace(son, idx++);
        }
        int src = 0;
        if (family.find(parent) != family.end()) {
            src = family[parent];
        } else {
            src = idx;
            family.emplace(parent, idx++);
        }
        adj_list[src].push_back(dest);
        root[dest]++;
    }
    start = std::find(root.begin(), root.end(), 0) - root.begin();
}

Graph ::Graph(std::vector<std::vector<int>> adj_list_)
    : adj_list(std::move(adj_list_))
{
}

auto Graph::bfs(int start) const -> std::vector<int>
{
    std::vector<int> sizes(adj_list.size(), 0);
    std::vector<bool> used(adj_list.size(), false);
    std::queue<int> queue;
    queue.push(start);
    while (!queue.empty()) {
        int qv = queue.front();
        queue.pop();
        used[qv] = true;
        for (auto to : adj_list[qv]) {
            if (!used[to]) {
                queue.push(to);
                sizes[to] = sizes[qv] + 1;
            }
        }
    }
    return sizes;
}
