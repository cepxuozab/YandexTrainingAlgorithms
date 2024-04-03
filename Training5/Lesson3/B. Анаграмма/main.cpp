#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <string_view>

constexpr int ALPHABET = 26;

auto CountSymbols(std::string_view str) -> std::array<int, ALPHABET> {
    std::array<int, ALPHABET> cnt{};
    for (char ch: str) {
        int idx = static_cast<int>(ch - 'a');
        cnt[idx]++;
    }
    return cnt;
}

auto IsAnagrams(std::string_view lhs, std::string_view rhs) -> bool {
    return CountSymbols(lhs) == CountSymbols(rhs);
}

auto main() -> int {
    std::string lhs, rhs;
    std::cin >> lhs >> rhs;
    IsAnagrams(lhs, rhs) ? puts("YES") : puts("NO");
}
