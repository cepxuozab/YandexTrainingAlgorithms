#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

auto Read()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& i : a) {
        std::cin >> i;
    }
    return a;
}

int main()
{
    freopen("input.txt", "r", stdin);
    std::vector<int> a(Read());
    std::sort(a.begin(), a.end());
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int low;
        int high;
        std::cin >> low >> high;
        auto left = std::lower_bound(a.begin(), a.end(), low);
        auto right = std::upper_bound(a.begin(), a.end(), high);
        std::cout << std::distance(left, right) << ' ';
    }
}
