#include <iostream>
#include <string>
#include <map>
#include <ranges>

void move_point(std::pair<short, short>& point, char dir)
{
    switch (dir)
    {
    case 'L':
        point.first -= 1;
        break;
    case 'R':
        point.first += 1;
        break;
    case 'U':
        point.second -= 1;
        break;
    case 'D':
        point.second += 1;
        break;
    default:
        throw "wrong data";
    }
}

auto main() -> int //NOLINT
{
    std::string path;
    std::cin >> path;
    std::map<std::pair<short, short>, int> table{{{0, 0}, 1}};
    std::pair<short, short> point{0, 0};
    int res = 0;
    for (char ch : path)
    {
        move_point(point, ch);
        table[point]++;
    }
    for (int u : std::views::values(table)) { res += (u > 1); }
    std::cout << res;
}
