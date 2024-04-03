#include <iostream>
#include <vector>

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<int> ropes(n);
    for (int &rope: ropes) {
        std::cin >> rope;
    }
    auto max = ropes[0];
    auto sum = ropes[0];

    for (int i = 1; i < n; ++i) {
        sum += ropes[i];
        max = ropes[i] > max ? ropes[i] : max;
    }

    const auto min = 2 * max - sum;

    std::cout << (min > 0 ? min : sum);
}
