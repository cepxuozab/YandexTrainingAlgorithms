#include <algorithm>
#include <iostream>
#include <vector>

auto const FASTIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();


int main()
{
    freopen("input.txt", "r", stdin);
    int64_t k, n;
    std::cin >> k >> n;
    std::vector<int> floor_people { 0 };
    for (int64_t i = 0; i < n; ++i) {
        int p;
        std::cin >> p;
        floor_people.push_back(p);
    }
    unsigned long long min_time = 0;
    int parking = 0;
    int curr_elevator_floor = parking;
    for (int64_t floor = n; floor > parking; --floor) {
        if (floor_people[floor] == 0) {
            continue;
        }
        min_time += std::abs(floor - curr_elevator_floor);
        curr_elevator_floor = floor;
        int rest = floor_people[floor] % k;
        int full_load_count = floor_people[floor] / k;
        if (full_load_count != 0) {
            min_time += (full_load_count * 2 - 1) * (floor - parking);
            floor_people[floor] -= (int64_t)full_load_count * k;
            floor_people[parking] += (int64_t)full_load_count * k;
            curr_elevator_floor = parking;
        }
        if (rest != 0) {
            min_time += std::abs(floor - curr_elevator_floor);
            floor_people[floor - 1] += rest;
            floor_people[floor] = 0;
            min_time += 1;
            curr_elevator_floor = floor - 1;
        }
    }
    std::cout << min_time << std::endl;
}
