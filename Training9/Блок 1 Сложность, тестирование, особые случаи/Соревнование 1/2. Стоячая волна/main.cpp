#include <iostream>
#include <vector>


struct Event
{
    long long l, r, x;
};


auto computeHeight(long long pos, std::vector<Event> const& events) -> long long
{
    long long height = 0;
    for (const auto& [l, r, x] : events)
    {
        if (pos >= l && pos <= r)
        {
            height += ((pos - l) % 2 == 0) ? x : -x;
        }
    }
    return height;
}

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;


    std::vector<Event> events;
    events.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        long long l, r, x;
        std::cin >> l >> r >> x;
        events.push_back({.l = l, .r = r, .x = x});
    }


    for (int i = 0; i < m; ++i)
    {
        long long q;
        std::cin >> q;
        std::cout << computeHeight(q, events) << '\n';
    }

    return 0;
}
