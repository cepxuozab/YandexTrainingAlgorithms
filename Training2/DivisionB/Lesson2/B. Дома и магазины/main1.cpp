#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

constexpr int INF = 1e6;

auto MaxPath(std::vector<short> const &buildings) -> int {
    auto prev_store_index = -INF;
    int const SIZE = static_cast<int>(buildings.size());
    auto answer = -INF;
    for (int i = 0; i < SIZE; ++i) {
        auto const &building = buildings[i];
        switch (building) {
            case 1: {
                auto next_store_index = i;
                while (next_store_index < SIZE and buildings[next_store_index] != 2)
                    next_store_index += 1;
                if (next_store_index >= SIZE)
                    next_store_index = INF;
                answer = std::max(answer, std::min(i - prev_store_index, next_store_index - i));
            }
                break;
            case 2:
                prev_store_index = i;
                break;
            default:
                break;
        }
    }
    return answer;
}

auto main()->int{
    constexpr int SIZE = 10;
    std::vector<short> buildings(SIZE);
    std::copy_n(std::istream_iterator<short>(std::cin), SIZE, buildings.begin());
    std::cout<<MaxPath(buildings);
}
