#include <iostream>
#include <print>
#include <set>

auto main() -> int {
    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::set<int> heap;
    std::set<int>::const_iterator it;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        size_t const size = heap.size();
        if (size == 0) {
            it = heap.insert(x).first;
        } else {
            bool less = x < *it;
            heap.insert(x);
            if (size % 2 == 0) {
                if (!less)
                    ++it;
            } else {
                if (less)
                    --it;
            }
        }

        std::print("{} ", *it);
    }
}
