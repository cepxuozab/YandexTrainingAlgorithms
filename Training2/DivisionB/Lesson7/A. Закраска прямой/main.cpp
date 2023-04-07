#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

enum class Event {

    IN, OUT
};

using Events = std::vector<std::pair<int64_t, Event>>;

auto ReadData(int n) -> Events;


auto LengthOfTheColoredPart(Events const& events) -> int64_t;

auto main() -> int
{
    int n;
    std::cin >> n;
    std::cout << LengthOfTheColoredPart(ReadData(n)) << std::endl;
    return 0;
}

auto ReadData(int n) -> Events
{
    Events events;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int left;
        int right;
        std::cin >> left >> right;
        events.emplace_back(left, Event::IN);
        events.emplace_back(right, Event::OUT);
    }
    std::sort(events.begin(), events.end());
    return events;
}


auto LengthOfTheColoredPart(Events const& events) -> int64_t
{
    int cnt = 0;
    int64_t sum = 0;
    int64_t last_x = events.front().first;
    for (auto const& [x, ev] : events) {
        switch (ev) {
        case Event::IN:
            last_x = cnt == 0 ? x : last_x;
            cnt++;
            break;
        case Event::OUT:
            sum += x - last_x;
            last_x = x;
            cnt--;
            break;
        default:
            break;
        }
    }
    return sum;
}
