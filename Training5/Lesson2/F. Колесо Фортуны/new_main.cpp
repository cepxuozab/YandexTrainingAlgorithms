#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

auto WheelOfFortunePrize(std::vector<int> const &sectors, int a, int b, int k) -> int {
    int n = static_cast<int>(sectors.size());
    int max_prize = 0;
    auto reversed_sectors = std::vector({sectors.front()});
    reversed_sectors.insert(reversed_sectors.end(), sectors.rbegin(), std::prev(sectors.rend()));
    auto end = b;
    if (static_cast<int64_t>(n) * k + a < b)end = n * k + a;
    for (int cur_speed = a; cur_speed <= end; cur_speed += k) {
        auto sector_i = ((cur_speed - 1) / k) % n;
        max_prize = std::max({max_prize, sectors[sector_i], reversed_sectors[sector_i]});
    }
    return max_prize;
}

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<int> sectors(n);
    for (int &sector: sectors)std::cin >> sector;
    int a, b, k;
    std::cin >> a >> b >> k;
    std::cout << WheelOfFortunePrize(sectors, a, b, k);
}