#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

auto main() -> int
{
    std::string str;
    getline(std::cin, str);
    int n = str.size();
    int b = 0;
    std::vector<int> bal(n);
    for (int i = 0; i < n; ++i) {
        str[i] == '(' ? b++ : b--;
        bal[i] = b;
    }
    int64_t ans = ((int64_t)(n + 1) * (n + 2)) / 2;
    int prevzero = -1;
    for (int pos = 0; pos < n; ++pos) {
        if (bal[pos] == 0) {
            ans += ((int64_t)(pos - prevzero - 1) * (pos - prevzero)) / 2;
            prevzero = pos;
        }
    }
    std::cout << ans;
    return 0;
}
