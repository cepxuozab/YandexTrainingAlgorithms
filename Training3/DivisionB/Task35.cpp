#include <iostream>
#include <vector>

static auto _ = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Graph {
public:
    Graph(size_t n)
        : graph(n + 1)
        , colors(n + 1, Color::WHITE)
        , parent(n + 1)

    {
    }
    [[nodiscard]] auto get_cycle() const -> std::vector<int> { return cycle; }
    [[nodiscard]] auto has_cycle() const -> bool { return is_cycle; }
    void add(int a, int b);
    void dfs_cycle(int u, int p);
    std::vector<std::vector<int>> graph;

private:
    enum class Color {
        WHITE,
        GREY,
        BLACK
    };
    std::vector<Color> colors;
    std::vector<int> cycle;
    std::vector<int> parent;
    bool is_cycle = false;
};
void Graph::add(int a, int b)
{
    graph[a].push_back(b);
}
void Graph::dfs_cycle(int u, int p)
{
    if (colors[u] == Color::BLACK || is_cycle) {
        return;
    }
    if (colors[u] == Color::GREY) {
        is_cycle = true;
        cycle.push_back(p);
        while (p != u) {
            p = parent[p];
            cycle.push_back(p);
        }
        return;
    }
    parent[u] = p;
    colors[u] = Color::GREY;
    for (int v : graph[u]) {
        if (v != parent[u]) {
            dfs_cycle(v, u);
        }
    }
    colors[u] = Color::BLACK;
}

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    Graph graph_(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int a;
            std::cin >> a;
            if (a != 0) {
                graph_.add(i, j);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        graph_.dfs_cycle(i, 0);
        if (graph_.has_cycle()) {
            break;
        }
    }
    //graph_.dfs_cycle(1, 0);
    auto arr = graph_.get_cycle();
    if (arr.empty()) {
        std::cout << "NO\n";
    }
    else {
        std::cout << "YES\n"
            << arr.size() << '\n';
        for (int i : arr) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
}
