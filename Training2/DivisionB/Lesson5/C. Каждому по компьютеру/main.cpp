#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    freopen("input.txt", "r", stdin);
    int m;
    int n;
    std::cin >> m >> n;
    std::vector<int> groups(m);
    for (int& peoples : groups) {
        std::cin >> peoples;
    }
    std::vector<int> idx_group(m);
    std::iota(idx_group.begin(), idx_group.end(), 0);
    std::sort(idx_group.begin(), idx_group.end(),
        [&](int i, int j) { return groups[i] > groups[j]; });
    std::vector<int> audience(n);
    for (int& computers : audience) {
        std::cin >> computers;
    }
    std::vector<int> idx_audience(n);
    std::iota(idx_audience.begin(), idx_audience.end(), 0);
    std::sort(idx_audience.begin(), idx_audience.end(),
        [&](int i, int j) { return audience[i] > audience[j]; });
    int num = 0;
    int j = 0;
    std::vector<int> answer(m);
    for (int i = 0; i < m; ++i) {
        if (groups[idx_group[i]] < audience[idx_audience[j]]) {
            answer[idx_group[i]] = idx_audience[j] + 1;
            j++;
            num++;
        }
    }
    std::cout << num << '\n';
    for (int ans : answer) {
        std::cout << ans << ' ';
    }
    return 0;
}
