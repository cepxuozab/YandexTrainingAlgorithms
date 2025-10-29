#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

enum class Type : char {
    END,
    START
};

struct Event {
    std::string time;
    Type type;

    auto operator<=>(Event const &) const = default;
};

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<Event> first, second;
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::cin >> line;
        auto pos = line.find('-');
        auto start = line.substr(0, pos);
        auto end = line.substr(pos + 1);
        first.push_back({start, Type::START});
        second.push_back({end, Type::END});
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::string line;
        std::cin >> line;
        auto pos = line.find('-');
        auto start = line.substr(0, pos);
        auto end = line.substr(pos + 1);
        second.push_back({start, Type::START});
        first.push_back({end, Type::END});
    }
    std::ranges::sort(first);
    std::ranges::sort(second);
    auto process_events = [](std::vector<Event> const &events) -> int {
        int bussesNeeded = 0, bussesAvailable = 0;
        for (auto const &[time, type]: events) {
            switch (type) {
                case Type::START:
                    bussesAvailable > 0 ? bussesAvailable-- : bussesNeeded++;
                    break;
                case Type::END:
                    bussesAvailable++;
                    break;
                default:
                    break;
            }
        }
        return bussesNeeded;
    };
    std::cout << process_events(first) + process_events(second);

}