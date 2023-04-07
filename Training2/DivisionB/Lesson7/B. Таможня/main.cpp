#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

enum class Event {
    OUT,
    IN
};

using Events = std::vector<std::pair<int, Event>>;

Events ReadData(int n);

int SmallestNumberOfDevices(Events const& events);

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::cout << SmallestNumberOfDevices(ReadData(n)) << std::endl;
    return 0;
}

Events ReadData(int n)
{
    Events events;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int arrival_time, treatment_time;
        std::cin >> arrival_time >> treatment_time;
        events.emplace_back(arrival_time, Event::IN);
        events.emplace_back(arrival_time + treatment_time, Event::OUT);
    }
    std::sort(events.begin(), events.end());
    return events;
}

int SmallestNumberOfDevices(Events const& events)
{
    int cnt = 0;
    int max_cnt = 0;
    for (auto const& [time, ev] : events) {
        switch (ev) {
        case Event::IN:

            max_cnt = std::max(++cnt, max_cnt);
            break;
        case Event::OUT:
            cnt--;
            break;
        default:
            break;
        }
    }
    return max_cnt;
}
