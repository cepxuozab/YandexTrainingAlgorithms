#include <iostream>
#include <set>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    if (!freopen("input.txt", "r", stdin)) {
        throw std::invalid_argument("can't read");
    }

    int n;
    int k;
    std::cin >> n >> k;
    std::set<int> work_day;
    for (int i = 1; i <= n; ++i) {
        if (i % 7 != 6 && i % 7 != 0) {
            work_day.insert(i);
        }
    }
    std::set<int> no_strike(work_day);
    for (int party = 0; party < k; party++) {
        int a;
        int b;
        std::cin >> a >> b;
        int max_strikes = (n - a) / b;
        for (int i = 0; i <= max_strikes; ++i) {
            no_strike.erase(a + b * i);
        }
    }
    std::cout << work_day.size() - no_strike.size() << '\n';
}
