#include <iostream>
#include <string>
#include <vector>

namespace {

    auto is_matching(char open, char close) -> bool {
        return (open == '(' && close == ')') ||
               (open == '[' && close == ']') ||
               (open == '{' && close == '}');
    }

} // namespace

auto main() -> int {
    std::string s;
    std::cin >> s;

    const int n = static_cast<int>(s.size());

    if (n == 0) {
        std::cout << "YES\n";
        return 0;
    }

    if (n % 2 != 0) {
        std::cout << "NO\n";
        return 0;
    }

    // Проверка по количеству скобок
    int cnt[256] = {};
    for (char c : s) {
        ++cnt[static_cast<unsigned char>(c)];
    }

    if (cnt['('] != cnt[')'] ||
        cnt['['] != cnt[']'] ||
        cnt['{'] != cnt['}']) {
        std::cout << "NO\n";
        return 0;
        }

    std::string t = s + s;



    for (int start = 0; start < n; ) {
        std::vector<char> st;
        int len = 0;

        int i = start;

        while (i < start + n) {
            char c = t[i];

            if (c == '(' || c == '[' || c == '{') {
                st.push_back(c);
            } else {
                if (st.empty() || !is_matching(st.back(), c)) {
                    break;
                }
                st.pop_back();
            }

            ++i;
            ++len;
        }

        if (len == n && st.empty()) {
            std::cout << "YES\n";
            return 0;
        }


        if (i == start) {
            ++start;
        } else {
            start = i;
        }
    }

    std::cout << "NO\n";
    return 0;
}