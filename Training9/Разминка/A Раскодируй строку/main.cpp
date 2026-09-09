#include <iostream>
#include <string>

auto main() -> int // NOLINT
{

    std::string str;
    std::cin >> str;
    std::string ans;
    while (!str.empty()) {
        char ch = str.back();
        str.pop_back();
        if (ch != '#') {
            int idx = ch - '0';
            idx--;
            ans.push_back('a' + idx);
        } else {
            int n = str.back() - '0';
            str.pop_back();
            int m = str.back() - '0';
            str.pop_back();
            n = m * 10 + n - 1;
            ans.push_back('a' + n);
        }
    }
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
        std::cout << *it;
    }
}
