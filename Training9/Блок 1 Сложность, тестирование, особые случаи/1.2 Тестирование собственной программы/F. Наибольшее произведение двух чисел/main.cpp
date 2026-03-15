#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>

auto main() -> int // NOLINT
{
    std::vector<int> arr(std::istream_iterator<int>(std::cin), {});
    int64_t first_min = std::numeric_limits<int>::max();
    int64_t first_max = std::numeric_limits<int>::min();
    auto second_min = first_min, second_max = first_max;
    for (int i : arr) {
        second_max = i > first_max ? std::exchange(first_max, i)
                                   : std::max<int64_t>(second_max, i);
        second_min = i < first_min ? std::exchange(first_min, i)
                                   : std::min<int64_t>(second_min, i);
    }
    if (first_max * second_max > first_min * second_min) {
        std::cout << second_max << ' ' << first_max;
    } else {
        std::cout << first_min << ' ' << second_min;
    }
}
