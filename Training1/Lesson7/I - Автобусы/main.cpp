#include <iostream>

#include <algorithm>
#include <numeric>
#include <vector>

struct Event {
    int city_id;
    int time;
    enum { IN = 0,
        OUT = 1 } type;
};

auto operator<(const Event& a, const Event& b) -> bool
{
    return a.time < b.time or (a.time == b.time and a.type < b.type);
}

auto operator>>(std::istream& in, Event& event) -> std::istream&
{
    int h;
    int m;

    in >> event.city_id >> h;
    in.ignore();
    in >> m;

    event.city_id -= 1;
    event.time = 60 * h + m;

    return in;
}

auto findBusOptimalNumber(std::istream& in) -> int
{
    int N;
    int M;
    in >> N >> M;

    std::vector<Event> events(2 * M);
    int bus_number = 0;
    for (int i = 0; i < 2 * M;) {
        in >> events[i];
        events[i++].type = Event::OUT;

        in >> events[i];
        events[i++].type = Event::IN;

        if (events[i - 2].time > events[i - 1].time) {
            bus_number += 1;
        }
    }
    std::sort(events.begin(), events.end());

    std::vector<int> cities_bus_counter(N);
    std::vector<int> cities_least_bus_number(N);
    for (auto [city, time, type] : events) {
        if (type == Event::IN) {
            cities_bus_counter[city] += 1;
        } else // type == Event::OUT
        {
            cities_bus_counter[city] -= 1;
            cities_least_bus_number[city] = std::min(
                cities_least_bus_number[city],
                cities_bus_counter[city]);
        }
    }

    if (std::any_of(cities_bus_counter.begin(), cities_bus_counter.end(),
            [](auto u) { return u != 0; })) {
        return -1;
    }

    return bus_number - std::reduce(cities_least_bus_number.begin(), cities_least_bus_number.end());
}

auto main() -> int
{
    std::cout << findBusOptimalNumber(std::cin);

    return 0;
}
