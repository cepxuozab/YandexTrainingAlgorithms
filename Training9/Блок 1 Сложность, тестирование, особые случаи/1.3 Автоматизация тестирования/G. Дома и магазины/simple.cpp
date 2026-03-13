#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <span>
#include <utility>

auto max_path(std::span<const short> buildings) -> int
{
    int ans = 0;
    for (int i = 0; std::cmp_less(i, buildings.size()); ++i) {
        if (buildings[i] == 1) { // нашли жилой дом
            int min_dist = static_cast<int>(buildings.size()); // большое начальное значение

            // ищем ближайший магазин
            for (int j = 0; std::cmp_less(j, buildings.size()); ++j) {
                if (buildings[j] == 2) { // нашли магазин
                    min_dist = std::min(min_dist, std::abs(i - j));
                }
            }

            ans = std::max(ans, min_dist);
        }
    }
    return ans;
}

auto main() -> int
{
    constexpr int SIZE = 10;
    std::vector<short> buildings(SIZE);
    std::copy_n(std::istream_iterator<short>(std::cin), SIZE, buildings.begin());
    std::cout << max_path(buildings);
}
