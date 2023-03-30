#include <algorithm>
#include <cstdint>
#include <iostream>

int main()
{
    int_fast64_t a, b, c;
    std::cin >> a >> b >> c;

    std::cout << std::max<int_fast64_t>(0, (3 * a + b - c + 2) / 3);

    return 0;
}
