#include <iostream>

auto main() -> int {
    int n;
    std::cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        int const tabs = num / 4;
        int tail = num % 4;
        tail = tail > 2 ? 2 : tail;
        sum += (tabs + tail);
    }
    std::cout << sum;
}
