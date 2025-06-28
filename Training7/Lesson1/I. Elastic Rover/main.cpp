#include <iostream>
#include <vector>
#include <tuple>
#include <optional>
#include <limits>
#include <algorithm>
#include <ranges>

struct Item {
    int v, c, p;
};

class ElasticRoverSolver {
    int n, s, max_v;
    std::vector<Item> items;

    using State = std::optional<std::tuple<int, int, int>>; // (cost, min_p, prev_item)

public:
    ElasticRoverSolver(int n_, int s_, std::vector<Item> items_)
        : n(n_), s(s_), items(std::move(items_)) {
        max_v = 0;
        for (const auto& item : items) {
            max_v += item.v;
        }
    }

    void solve() const {
        std::vector<std::vector<State>> dp(n + 1, std::vector<State>(max_v + 1));

        dp[0][0] = std::tuple{0, std::numeric_limits<int>::max(), 0};

        for (int item_i = 1; item_i <= n; ++item_i) {
            dp[item_i] = dp[item_i - 1];  // Copy previous row
            const auto& item = items[item_i];

            for (int v_i = max_v - item.v; v_i >= 0; --v_i) {
                if (!dp[item_i - 1][v_i]) continue;

                auto [prev_cost, prev_p, _] = *dp[item_i - 1][v_i];
                int new_v = v_i + item.v;

                if (item.p < new_v - s) continue;

                int new_cost = prev_cost + item.c;
                int new_p = std::min(prev_p, item.p);

                if (!dp[item_i][new_v]) {
                    dp[item_i][new_v] = std::tuple{new_cost, new_p, item_i};
                } else {
                    auto [cur_cost, cur_p, __] = *dp[item_i][new_v];
                    if (new_cost > cur_cost || (new_cost == cur_cost && new_p > cur_p)) {
                        dp[item_i][new_v] = std::tuple{new_cost, new_p, item_i};
                    }
                }
            }
        }

        int best_cost = 0, best_row = 0, best_col = 0;
        for (int row = 0; row <= n; ++row) {
            for (int col = 1; col <= max_v; ++col) {
                if (!dp[row][col]) continue;
                auto [cost, p, _] = *dp[row][col];
                if (p < col - s) continue;

                if (cost > best_cost) {
                    best_cost = cost;
                    best_row = row;
                    best_col = col;
                }
            }
        }

        std::vector<int> result;
        int item_i = std::get<2>(*dp[best_row][best_col]);
        int col = best_col;

        while (item_i > 0) {
            result.push_back(item_i);
            col -= items[item_i].v;
            item_i = std::get<2>(*dp[item_i - 1][col]);
        }

        std::ranges::reverse(result);

        std::cout << result.size() << ' ' << best_cost << '\n';
        for (int id : result)
            std::cout << id << ' ';
        std::cout << '\n';
    }

    static ElasticRoverSolver read_input() {
        int n, s;
        std::cin >> n >> s;
        std::vector<Item> items = {{0, 0, 0}};  // 1-based indexing
        for (int i = 0; i < n; ++i) {
            int v, c, p;
            std::cin >> v >> c >> p;
            items.push_back({v, c, p});
        }
        return ElasticRoverSolver(n, s, std::move(items));
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solver = ElasticRoverSolver::read_input();
    solver.solve();
    return 0;
}
