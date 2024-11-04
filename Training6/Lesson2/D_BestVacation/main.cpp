#include <algorithm>
#include <iostream>
#include <queue>

template <typename T>
auto operator>>(std::istream& input, std::vector<T>& arr) -> std::istream& {
    for (auto& a : arr) input >> a;
    return input;
}

auto main() -> int {  // NOLINT
    int n, k;
    std::cin >> n >> k;
    std::vector<int> activity_directions(n);
    std::cin >> activity_directions;
    std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;
    std::ranges::sort(activity_directions);
    for (auto& affair : activity_directions) {
        if (!min_heap.empty() && affair - min_heap.top() > k) {
            min_heap.pop();
        }
        min_heap.push(affair);
    }
    std::cout << min_heap.size();
}