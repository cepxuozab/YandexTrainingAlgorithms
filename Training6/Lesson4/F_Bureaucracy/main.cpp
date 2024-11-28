#include <cstdint>
#include <iostream>
#include <span>
#include <vector>

auto CountMoney(std::span<int> bosses) -> std::vector<int64_t> {
    size_t const n = bosses.size();
    std::vector<std::vector<int>> children(n + 1);
    int idx = 1;
    for (auto boss : bosses) {
        children[boss - 1].push_back(idx++);
    }
    std::vector<int64_t> ans(n + 1);
    auto cnt_money = [&](auto&& self, int num) -> std::tuple<int64_t, int64_t> {
        int64_t size = 1;
        for (auto& child : children[num]) {
            auto [c_money, c_size] = self(self, child);
            ans[num] += c_money + c_size;
            size += c_size;
        }
        ans[num] += 1;
        return {ans[num], size};
    };
    cnt_money(cnt_money, 0);
    return ans;
}

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<int> bosses(n - 1);
    for (int& boss : bosses) {
        std::cin >> boss;
    }
    for (auto money : CountMoney(bosses)) {
        std::cout << money << ' ';
    }
}
