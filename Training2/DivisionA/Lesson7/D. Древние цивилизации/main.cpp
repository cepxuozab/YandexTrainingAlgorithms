#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct Event {
    int64_t x;
    int idx;
    Event()
        : x{}
        , idx{}
    {
    }
    Event(int64_t x_, int idx_)
        : x(x_)
        , idx(idx_)
    {
    }
    bool operator<(Event const& other) const
    {
        return x < other.x;
    }
};
int main()
{
    //freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<Event> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int64_t l, r;
        std::cin >> l >> r;
        events.emplace_back(2LL * l, i);
        events.emplace_back(2LL * r - 1, i);
    }
    std::sort(events.begin(), events.end());
    int k = 0;
    int64_t best = 0;
    int p = 0;
    int q = 0;
    int j = 0;
    for (int i = 0; i + 1 < (int)events.size(); ++i) {
        if (events[i].x % 2 == 0) {
            k++;
            if (k > 1 && (events[i + 1].x % 2 != 0)) {
                int64_t t = (events[i + 1].x + 1) / 2 - events[i].x / 2;
                if (best == 0 || t < best) {
                    best = t;
                    j = i;
                    p = events[i].idx;
                    q = events[i + 1].idx;
                }
            }
        }
        else {
            k--;
        }
    }
    if (best == 0) {
        std::cout << 0 << '\n';
        return 0;
    }
    if (p == q) {
        std::vector<bool> u(n, false);
        for (int i = 0; i < j; ++i) {
            u[events[i].idx] = (events[i].x % 2 == 0);
        }
        for (int i = 0; i < n; ++i) {
            if (i != p && u[i]) {
                q = i;
            }
        }
    }
    std::cout << std::min(p, q) + 1 << ' ' << std::max(p, q) + 1 << '\n';
}
