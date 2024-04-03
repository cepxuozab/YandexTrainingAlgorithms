#include <cstdint>
#include <iostream>
#include <string>


auto main() -> int {
    int64_t n, k, d;
    std::cin >> n >> k >> d;
    n *= 10;
    for (int i = 0; i < 10; i++) {
        if ((n + i) % k == 0) {
            n += i;
            auto str = std::to_string(n);
            str.append(std::string(d - 1, '0'));
            std::cout << str;
            return 0;
        }
    }
    std::cout << -1;
}