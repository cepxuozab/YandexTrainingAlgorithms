#include <iostream>
#include <vector>
#include <string>

auto numbers_way_place_domino(std::vector<std::string> const& field) -> int
{
    int count = 0;
    for (const auto& row : field)
    {
        for (size_t j = 0; j + 1 < row.size(); ++j)
        {
            count += (row[j] == '.' && row[j + 1] == '.');
        }
    }


    for (size_t i = 0; i + 1 < field.size(); ++i)
    {
        for (size_t j = 0; j < field[i].size(); ++j)
        {
            count += (field[i][j] == '.' && field[i + 1][j] == '.');
        }
    }
    return count;
}


auto main() -> int
{ //NOLINT
    int n, m;
    std::cin >> n >> m;


    std::vector<std::string> field(n);
    for (auto& line : field)std::cin >> line;
    std::cout << numbers_way_place_domino(field);
}
