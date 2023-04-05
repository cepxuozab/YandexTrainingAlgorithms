#include <algorithm>
#include <array>
#include <iostream>
#include <string>

int main()
{
    if (!freopen("input.txt", "r", stdin)) {
        throw std::invalid_argument("can't read");
    }
    int n;
    std::cin >> n;
    std::string str;
    std::cin >> str;
    std::array<int, 26> dict{};
    for (char ch : str) {
        dict[ch - 'A']++;
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        for (int i = 0; i < dict[ch - 'A'] / 2; ++i) {
            std::cout << ch;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (dict[ch - 'A'] & 1) {
            std::cout << ch;
            break;
        }
    }
    for (char ch = 'Z'; ch >= 'A'; --ch) {
        for (int i = 0; i < dict[ch - 'A'] / 2; ++i) {
            std::cout << ch;
        }
    }
    return 0;
}

