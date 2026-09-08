#include <algorithm>
#include <iostream>
#include <print>

auto count_operations(int n) -> long long {
    if (n == 1)
        return 1LL;
    return 2LL * count_operations(n - 1) + 1;
}

void hanoy_tower(int n, int start, int finish) {
    if (n == 1)
        std::print("{} {} {}\n",n, start, finish);
    else {
        auto tmp = 6 - start - finish;
        hanoy_tower(n - 1, start, tmp);
        std::print("{} {} {}\n",n, start, finish);
        hanoy_tower(n - 1, tmp, finish);
    }
}

auto main() -> int {
    int n;
    std::cin >> n;  
    hanoy_tower(n, 1, 3);
    return 0;
}