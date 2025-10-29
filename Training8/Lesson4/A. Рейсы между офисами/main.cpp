#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cctype>
#include <string>

auto timeToMinutes(const std::string &s) -> int {
    int h = std::stoi(s.substr(0, 2));
    int m = std::stoi(s.substr(3, 2));
    return h * 60 + m;
}

struct Trip {
    int dep{}, arr{};
    bool fromA = false;
};

auto parseTime(const std::string &line) -> std::pair<int, int> {
    size_t pos = line.find('-');
    auto dep_str = line.substr(0, pos);
    auto arr_str = line.substr(pos + 1);
    int dep = timeToMinutes(dep_str);
    int arr = timeToMinutes(arr_str);
    return {dep, arr};
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N >> std::ws;
    std::vector<Trip> trips;
    std::string line;

    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        auto [dep, arr] = parseTime(line);
        trips.push_back({dep, arr, true});
    }

    int M;
    std::cin >> M >> std::ws;

    for (int i = 0; i < M; ++i) {
        std::getline(std::cin, line);
        auto [dep, arr] = parseTime(line);
        trips.push_back({dep, arr, false});
    }

    std::ranges::sort(trips, {}, &Trip::dep);

    using min_heap = std::priority_queue<int, std::vector<int>, std::greater<>>;
    min_heap available_at_A;
    min_heap available_at_B;

    int total_buses = 0;

    auto perform = [](const Trip &trip, min_heap &from_heap, min_heap &to_heap) -> bool {
        bool need_new_bus = true;
        if (!from_heap.empty() && from_heap.top() <= trip.dep) {
            from_heap.pop();
            need_new_bus = false;
        }
        to_heap.push(trip.arr);
        return need_new_bus;
    };

    for (const auto &trip: trips) {
        if (trip.fromA) {
            if (perform(trip, available_at_A, available_at_B)) {
                ++total_buses;
            }
        } else {
            if (perform(trip, available_at_B, available_at_A)) {
                ++total_buses;
            }
        }
    }

    std::cout << total_buses << "\n";
    return 0;
}