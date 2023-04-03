#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

[[maybe_unused]] static auto const FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();



int main()
{
    std::unordered_set<int> sets;

    for (int x; std::cin >> x;) {
        auto [_, IsSuccess] = sets.insert(x);
        IsSuccess ? puts("NO") : puts("YES");
    }
    return 0;
}
