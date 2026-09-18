#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

[[nodiscard]] std::int64_t CostWithShift(const std::vector<std::int64_t>& heights, std::int64_t shift) {
    std::vector<std::int64_t> adjusted(heights);
    for (std::size_t i = 1; i < adjusted.size(); i += 2) {
        adjusted[i] -= shift;
    }

    const auto middle = adjusted.begin() + static_cast<std::ptrdiff_t>(adjusted.size() / 2);
    std::ranges::nth_element(adjusted, middle);
    const std::int64_t median = *middle;

    std::int64_t cost = 0;
    for (const std::int64_t value : adjusted) {
        cost += value > median ? value - median : median - value;
    }
    return cost;
}

int main() {
    std::size_t n{};
    std::int64_t k{};
    std::cin >> n >> k;

    std::vector<std::int64_t> heights(n);
    for (std::int64_t& height : heights) {
        std::cin >> height;
    }

    std::cout << std::min(CostWithShift(heights, k), CostWithShift(heights, -k)) << '\n';
}