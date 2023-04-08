#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n, m;
    std::cin >> n >> m;
    std::vector<int> visited(m, true);
    std::vector<std::pair<int, int>> segments;
    segments.reserve(m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        segments.emplace_back(x, y);
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            if (!visited[j])
                continue;
            auto [a, b] = segments[i];
            auto [c, d] = segments[j];
            if (a <= d && c <= b) {
                visited[j] = false;
            }
        }
    }
    std::cout << std::count(visited.begin(), visited.end(), true);
    return 0;
}
