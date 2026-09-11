#include <deque>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

auto main() -> int {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int& a : arr) std::cin >> a;
    std::deque<int> deque;
    auto clear = [&]() -> void {
        while (deque.size() > 1 && deque.back() < deque[deque.size() - 2]) {
            std::swap(deque.back(), deque[deque.size() - 2]);
            deque.pop_back();
        }
    };
    for (auto i : std::ranges::views::iota(0, k)) {
        int x = arr[i];
        deque.push_back(x);
        clear();
    }
    std::println("{}", deque.front());
    for (auto i : std::ranges::views::iota(k, n)) {
        if (deque[0] == arr[i - k] or std::size(deque) > k) deque.pop_front();
        deque.push_back(arr[i]);
        clear();
        std::println("{}", deque.front());
    }
}