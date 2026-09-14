#include <deque>
#include <exception>
#include <iostream>
#include <span>
#include <vector>

static auto max_fish_profit(int n, int k, std::span<const int> prices) {
    if (n < 2 || k < 1)
        return 0;
    std::deque<int> min_queue;
    int max_profit = 0;
    for (int i = 0; i < n; ++i) {
        if (!min_queue.empty() && min_queue.front() < i - k) {
            min_queue.pop_front();
        }
        if (!min_queue.empty()) {
            max_profit = std::max(max_profit, prices[i] - prices[min_queue.front()]);
        }
        while (!min_queue.empty() && prices[min_queue.back()] >= prices[i]) {
            min_queue.pop_back();
        }
        min_queue.push_back(i);
    }
    return max_profit;
}

auto main() -> int {

    freopen("input.txt", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> prices(n);
    for (auto& price : prices) {
        std::cin >> price;
    }
    std::printf("%d\n", max_fish_profit(n, k, prices));

    return 0;
}
