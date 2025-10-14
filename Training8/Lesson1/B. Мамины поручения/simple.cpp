#include <iostream>
#include <iomanip>
#include <algorithm>

auto main() -> int {
    double a, b, c, v0, v1, v2;
    std::cin >> a >> b >> c >> v0 >> v1 >> v2;
    a = std::min(a, b + c);
    b = std::min(b, a + c);
    auto var1 = a / v0 + a / v1 + b / v0 + b / v1;
    auto var2 = a / v0 + c / v1 + b / v2;
    auto var3 = b / v0 + c / v1 + a / v2;
    std::cout << std::setprecision(9) << std::min({var1, var2, var3});
}