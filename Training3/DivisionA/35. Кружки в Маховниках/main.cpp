#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <ranges>
#include <set>
#include <vector>

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n);
    std::vector<int> inDegree(n, 0);
    std::vector<int> order;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        for (int j = 0; j < a; j++) {
            int to;
            std::cin >> to;
            to--;
            graph[i].push_back(to);
            inDegree[to]++;
        }
    }
    std::priority_queue<int> heap;

    for (size_t i = 0; i < inDegree.size(); ++i) {
        if (inDegree[i] == 0) {
            heap.emplace(i);
        }
    }
    while (!heap.empty()) {
        auto v = heap.top();
        heap.pop();
        order.push_back(v + 1);
        for (int to : graph[v]) {
            if (--inDegree[to] == 0) {
                heap.push(to);
            }
        }
    }
    std::ranges::reverse_copy(order, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
