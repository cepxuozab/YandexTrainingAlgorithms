#include <iostream>
#include <utility>
#include <vector>

namespace {

void heapify(std::vector<int>& a) {
    int cnt = 0;
    auto down = [&](this auto&& self, int i) -> void {
        int left = 2 * i + 1;
        int right = left + 1;
        if (left < a.size()) {
            int next = left;
            if (right < a.size() && a[right] > a[left]) {
                next = right;
            }
            if (a[next] > a[i]) {
                std::swap(a[next], a[i]);
                cnt++;
                self(next);
            }
        }
    };
    for (int i = a.size() - 1; i >= 0; i--) {
        down(i);
    }

    std::cout << cnt << '\n';
}
} // namespace

auto main() -> int {
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) {
        std::cin >> a;
    }
    heapify(arr);
}
