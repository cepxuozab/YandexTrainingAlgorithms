#include <algorithm>
#include <iostream>
#include <vector>

struct Event {
    int coord_ = 0;
    int type_ = 0;
    int index_ = 0;
    Event() = default;
    Event(int coord, int type, int idx)
        : coord_(coord)
        , type_(type)
        , index_(idx)
    {
    }
    bool operator<(Event const& other) const
    {
        return coord_ < other.coord_
            || coord_ == other.coord_
            && type_ > other.type_;
    }
};

auto main() -> int
{
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<Event> events;
    events.reserve(n);
    for (int i = 0; i < n; ++i) {
        int left;
        int right;
        std::cin >> left >> right;
        if (right < left) {
            std::swap(left, right);
        }
        events.emplace_back(left, 1, i);
        events.emplace_back(right, -1, i);
    }
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        events.emplace_back(x, 0, i);
    }
    std::vector<int64_t> answer(m);
    sort(events.begin(), events.end());
    int64_t opened = 0;
    for (auto const& [x, type, idx] : events) {
        opened += type;
        if (type == 0) {
            answer[idx] = opened;
        }
    }
    for (auto i : answer) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
