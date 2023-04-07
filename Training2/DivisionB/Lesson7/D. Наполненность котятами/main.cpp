#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

enum class Kitten {
    IN,
    CAT,
    OUT
};

using Event = std::tuple<int, Kitten, int>;

auto ReadData(int n, int m) -> std::vector<Event>;

auto CountCoating(std::vector<Event> const& events, int m) -> std::vector<int>;

void PrintVector(std::vector<int> const& ans);

auto main() -> int
{
    int n;
    int m;
    std::cin >> n >> m;
    PrintVector(CountCoating(ReadData(n, m), m));
    return 0;
}

auto ReadData(int n, int m) -> std::vector<Event>
{
    std::vector<Event> events;
    events.reserve(2 * m + n);
    for (int i = 0; i < n; ++i) {
        int cat;
        std::cin >> cat;
        events.emplace_back(cat, Kitten::CAT, -1);
    }
    for (int i = 0; i < m; ++i) {
        int left;
        int right;
        std::cin >> left >> right;
        events.emplace_back(left, Kitten::IN, i);
        events.emplace_back(right, Kitten::OUT, i);
    }
    std::sort(events.begin(), events.end());
    return events;
}

auto CountCoating(std::vector<Event> const& events, int m) -> std::vector<int>
{
    std::vector<int> ans(m);
    std::vector<int> cnts(m);
    int cnt = 0;
    for (auto const& [x, ev, idx] : events) {
        switch (ev) {
        case Kitten::IN:
            cnts[idx] -= cnt;
            break;
        case Kitten::CAT:
            cnt++;
            break;
        default:
            ans[idx] = cnt + cnts[idx];
            break;
        }
    }
    return ans;
}

void PrintVector(std::vector<int> const& ans)
{
    for (int a : ans) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;
}
