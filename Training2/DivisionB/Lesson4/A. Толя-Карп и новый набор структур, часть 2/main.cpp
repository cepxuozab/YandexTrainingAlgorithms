#include <iostream>
#include <map>

static auto const FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    int n;
    std::cin >> n;
    std::map<int64_t, int64_t> maps;
    for (int i = 0; i < n; ++i) {
        int64_t a;
        int64_t b;
        std::cin >> a >> b;
        maps[a] += b;
    }
    for (auto const& [key, value] : maps) {
        std::cout << key << ' ' << value << '\n';
    }
}
