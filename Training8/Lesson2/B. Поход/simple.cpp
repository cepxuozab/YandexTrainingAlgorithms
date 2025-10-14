#include <iostream>
#include <string>
#include <algorithm>



auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string str;
    std::cin >> str;
    int left = 0, right = 1;
    for (char ch: str) {
        auto value = std::min(left, right) + 1;
        switch (ch) {
            case 'L':
                left = value;
                break;
            case 'R':
                right = value;
                break;
            default:
                left += 1;
                right += 1;
        }
    }
    std::cout << right;
}