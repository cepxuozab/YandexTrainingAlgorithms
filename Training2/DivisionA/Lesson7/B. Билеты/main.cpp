#include <iostream>
#include <cmath>

int main()
{
    uint64_t a, b, c, x, k;
    std::cin >> a >> b >> c >> x >> k;

    std::cout << (x / k < a || x / k > b ? x / k
        : std::max(uint64_t(double(x * 100) / (k * (c + 100))), a - 1));

    return 0;
}