#include <iostream>

auto main() -> int {
    short g1, g2, q1, q2, m;
    char ch;
    std::cin >> g1 >> ch >> g2 >> q1 >> ch >> q2 >> m;
    auto result = g2 + q2 - g1 - q1;

    if (result < 0) {
        result = 0;
    } else {
        if ((m == 1 && g2 >= q1 + result) || (m == 2 && q2 >= g1)) {
            result++;
        }
    }
    std::cout << result;
}