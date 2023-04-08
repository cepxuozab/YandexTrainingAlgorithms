#include <cstdint>
#include <iostream>

static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n;
    std::cin >> n;
    int64_t ans = 0;
    int min;
    std::cin >> min;
    for (int i = 1; i < n; ++i) {
        int val;
        std::cin >> val;
        ans += (min < val ? min : val);
        min = val;
    }
    std::cout << ans << std::endl;
}
