#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using Event = std::pair<int, int>;

int main()
{
    freopen("input.txt", "r", stdin);
    int m;
    std::cin >> m;
    std::vector<Event> events;
    int i = 0;
    for (int l, r; std::cin >> l >> r;) {
        if (l == 0 && r == 0) {
            break;
        }
        if (r < 0 || l > m) {
            continue;
        }
        events.emplace_back(l, r);
    }
    std::sort(events.begin(), events.end());
    std::vector<Event> ans;
    int nowright = 0;
    int nextright = 0;
    Event nowbest{};
    for (auto const& [left, right] : events) {
        if (left > nowright) {
            ans.push_back(nowbest);
            nowright = nextright;
            if (nowright > m) {
                break;
            }
        }
        if (left <= nowright && right > nextright) {
            nextright = right;
            nowbest = { left,right };
        }
    }
    if (nowright < m) {
        nowright = nextright;
        ans.push_back(nowbest);
    }
    if (nowright < m) {
        std::cout << "No solution\n";
    }
    else {
        std::cout << ans.size() << '\n';
        for (auto const& [l, r] : ans) {
            std::cout << l << ' ' << r << '\n';
        }
    }
}
