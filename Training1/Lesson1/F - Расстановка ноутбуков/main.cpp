#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <tuple>

auto Notebooks(int widthFirst, int lengthFirst, int widthSecond, int lengthSecond) -> std::pair<int, int>
{
    std::array<int, 4> m {};
    std::array<int, 4> n {};
    int min = INT_MAX;
    m[0] = widthFirst > lengthSecond ? widthFirst : lengthSecond;
    n[0] = lengthFirst + widthSecond;
    m[1] = widthFirst > widthSecond ? widthFirst : widthSecond;
    n[1] = lengthFirst + lengthSecond;
    m[2] = lengthFirst > widthSecond ? lengthFirst : widthSecond;
    n[2] = widthFirst + lengthSecond;
    m[3] = lengthFirst > lengthSecond ? lengthFirst : lengthSecond;
    n[3] = widthFirst + widthSecond;
    int length = 0;
    int width = 0;
    for (int i = 0; i < 4; ++i) {
        if (m[i] * n[i] < min) {
            min = m[i] * n[i];
            std::tie(length, width) = { m[i], n[i] };
        }
    }
    return { length, width };
}

auto main() -> int
{
    int widthFirst;
    int lengthFirst;
    int widthSecond;
    int lengthSecond;

    std::cin >> widthFirst >> lengthFirst >> widthSecond >> lengthSecond;
    auto [length, width] = Notebooks(widthFirst, lengthFirst, widthSecond, lengthSecond);
    std::cout << length << ' ' << width;
    return 0;
}
