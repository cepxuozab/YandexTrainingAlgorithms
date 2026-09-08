#include <cctype>
#include <iostream>
#include <string>
#include <string_view>

auto snake_case(std::string_view str) -> std::string {
    std::string result;
    for (char c : str) {
        if (std::isupper(c)) {
            if (!result.empty()) {
                result += '_';
            }
            result += std::tolower(c);
        } else {
            result += c;
        }
    }
    return result;
}

auto main() -> int {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string str;
        std::cin >> str;
        std::cout << snake_case(str) << std::endl;
    }
}