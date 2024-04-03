#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
auto findMax(const std::vector<std::vector<int>>& forces, int rowExclude, int columnExclude)
    -> std::tuple<int, size_t, size_t> {
    bool first = true;
    int maxValue{};
    size_t maxRow{}, maxColumn{};
    for (size_t i = 0; i < forces.size(); ++i) {
        if (std::cmp_equal(i, rowExclude)) continue;
        for (size_t j = 0; j < forces.at(i).size(); ++j) {
            if (std::cmp_equal(j, columnExclude)) continue;
            if (first) {
                maxValue = forces.at(i).at(j);
                maxRow = i;
                maxColumn = j;
                first = false;
            } else if (maxValue < forces.at(i).at(j)) {
                maxValue = forces.at(i).at(j);
                maxRow = i;
                maxColumn = j;
            }
        }
    }
    return {maxValue, maxRow, maxColumn};
}

auto main() -> int {
    int n, m;
    std::cin >> n >> m;
    int maxForceGlobal = 0;
    int iMaxForce = 0;
    int jMaxForce = 0;
    bool first = true;
    int force;
    auto forces = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> force;
            if (first) {
                maxForceGlobal = force;
                iMaxForce = i;
                jMaxForce = j;
                first = false;
            } else if (force > maxForceGlobal) {
                maxForceGlobal = force;
                iMaxForce = i;
                jMaxForce = j;
            }
            forces[i][j] = force;
        }
    }
    // strategy Row->Column
    int maxValueWithoutRow;
    int i, j;
    int row1 = iMaxForce;
    std::tie(maxValueWithoutRow, i, j) = findMax(forces, row1, -1);
    int column1 = j;
    int maxValueWithoutRowColumn;
    std::tie(maxValueWithoutRowColumn, i, j) = findMax(forces, row1, column1);

    // strategy Row->Column
    int maxValueWithoutColumn;
    int column2 = jMaxForce;
    std::tie(maxValueWithoutColumn, i, j) = findMax(forces, -1, column2);
    int row2 = i;
    int maxValueWithoutColumnRow;
    std::tie(maxValueWithoutColumnRow, i, j) = findMax(forces, row2, column2);
    int resultRow, resultColumn;

    if (maxValueWithoutRowColumn < maxValueWithoutColumnRow) {
        resultRow = row1;
        resultColumn = column1;
    } else {
        resultRow = row2;
        resultColumn = column2;
    }

    std::cout << (resultRow + 1) << " " << (resultColumn + 1);
}
