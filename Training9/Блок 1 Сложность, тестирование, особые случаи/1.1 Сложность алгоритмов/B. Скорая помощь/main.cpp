#include <iostream>

auto get_entrance_and_floor(int flat_no, int flats_on_floor, int floors) -> std::pair<int, int>
{
    auto floor_before = (flat_no - 1) / flats_on_floor;
    auto entrance = floor_before / floors + 1;
    int floor = floor_before % floors + 1;
    return {entrance, floor};
}

auto check(int k1, int m, int k2, int p2, int n2, int flats_on_floor) -> std::pair<int, int>
{
    auto [entrance2, floor2] = get_entrance_and_floor(k2, flats_on_floor, m);
    if (entrance2 == p2 && floor2 == n2)
        return get_entrance_and_floor(k1, flats_on_floor, m);
    return {-1, -1};
}

auto main() -> int
{
    int k1, m, k2, p2, n2;
    std::cin >> k1 >> m >> k2 >> p2 >> n2;
    int ent = -1, floor = -1;
    bool good_flag = false;
    for (int flat_on_floor = 1; flat_on_floor < 1'000'001; ++flat_on_floor)
    {
        auto [n_ent, n_floor] = check(k1, m, k2, p2, n2, flat_on_floor);
        if (n_ent != -1)
        {
            good_flag = true;
            if (ent == -1)
                ent = n_ent, floor = n_floor;
            else if (ent != n_ent && ent != 0)ent = 0;
            else if (floor != n_floor && floor != 0)floor = 0;
        }
    }
    if (good_flag)
    {
        std::cout << ent << ' ' << floor << '\n';
    }
    else std::cout << -1 << ' ' << -1 << '\n';
}
