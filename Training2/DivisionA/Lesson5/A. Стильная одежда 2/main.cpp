#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

template <typename T>
auto operator>>(std::istream& input, std::vector<T>& arr) -> std::istream&
{
    int n;
    input >> n;
    arr.resize(n);
    for (auto& elem : arr) {
        input >> elem;
    }
    sort(arr.begin(), arr.end());
    return input;
}

auto main() -> int
{
    freopen("input.txt", "r", stdin);

    std::vector<int> caps, tank_tops, pants, boots;
    std::cin >> caps >> tank_tops >> pants >> boots;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    int min = std::min(std::min(caps[0], tank_tops[0]), std::min(pants[0], boots[0]));
    int max = std::max(std::max(caps[0], tank_tops[0]), std::max(pants[0], boots[0]));
    int diff = std::abs(max - min);
    int min1 = i1, min2 = i2, min3 = i3, min4 = i4;
    int n1 = caps.size(), n2 = tank_tops.size(), n3 = pants.size(), n4 = boots.size();
    while (i1 < n1 && i2 < n2 && i3 < n3 && i4 < n4) {
        min = std::min(std::min(caps[i1], tank_tops[i2]), std::min(pants[i3], boots[i4]));
        max = std::max(std::max(caps[i1], tank_tops[i2]), std::max(pants[i3], boots[i4]));
        int diffR = std::abs(max - min);

        if (diffR < diff) {
            diff = diffR;
            min1 = i1;
            min2 = i2;
            min3 = i3;
            min4 = i4;
        }

        if (diffR < 1) {
            break;
        }

        while (min == caps[i1]) {
            i1++;
        }
        while (min == tank_tops[i2]) {
            i2++;
        }

        while (min == pants[i3]) {
            i3++;
        }

        while (min == boots[i4]) {
            i4++;
        }
    }
    std::cout << caps[min1] << ' '
        << tank_tops[min2] << ' '
        << pants[min3] << ' '
        << boots[min4] << '\n';
}
