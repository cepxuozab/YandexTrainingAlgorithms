#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <cassert>

struct Position {
    int row{};
    int column{};
};

auto ReadShips(int n, std::istream &input = std::cin) -> std::vector<Position>;

auto MinimumNumbersOfMoves(std::vector<Position> const &ships) -> int;

void Test();

auto main() -> int {
    Test();
    int n;
    std::cin >> n;
    auto const ships = ReadShips(n);
    std::cout << MinimumNumbersOfMoves(ships) << '\n';
}

auto ReadShips(int n, std::istream &input) -> std::vector<Position> {
    std::vector<Position> ships(n);
    for (auto &[row, column]: ships) {
        input >> row >> column;
    }
    return ships;
}

auto MinimumNumbersOfMoves(std::vector<Position> const &ships) -> int {
    int n = static_cast<int>(ships.size());
    auto distances = std::vector<int>(n, 0);
    std::map<int, int> rowToCount;
    for (int i = 0; i < n; ++i) {
        auto const &[row, column] = ships.at(i);
        for (int j = 0; j < n; ++j) {
            distances[j] += abs(j + 1 - column);
        }
        rowToCount[row]++;
    }
    auto horizontalSteps = std::ranges::min(distances);
    std::vector<int> orderedRows;
    orderedRows.reserve(n);
    for (auto const &[row_num, cnt]: rowToCount) {
        for (int i = 0; i < cnt; ++i) {
            orderedRows.push_back(row_num);
        }
    }
    int verticalSteps = 0;
    for (int i = 0; i < n; ++i) {
        verticalSteps += abs(orderedRows.at(i) - (i + 1));
    }
    return horizontalSteps + verticalSteps;
}

void Test() {
    {
        std::stringstream ss(
                "3 7 "
                "7 10 "
                "4 9 "
                "2 2 "
                "5 9 "
                "8 2 "
                "5 5 "
                "10 4 "
                "2 10 "
                "6 5 "
        );
        auto arr = ReadShips(10, ss);
        auto result = MinimumNumbersOfMoves(arr);
        assert(result == 32);
        std::cerr << "test one passed\n";
    }
    {
        std::stringstream ss(
                "1 1 "
                "2 2 "
                "3 3 "
                "4 4 "
                "5 5 "
        );
        auto arr = ReadShips(5, ss);
        auto result = MinimumNumbersOfMoves(arr);
        assert(result == 6);
        std::cerr << "test two passed\n";
    }
    {
        std::stringstream ss(
                "4 4 "
                "10 2 "
                "5 5 "
                "5 1 "
                "1 8 "
                "9 3 "
                "9 6 "
                "8 5 "
                "1 9 "
                "4 5 "
        );
        auto arr = ReadShips(10, ss);
        auto result = MinimumNumbersOfMoves(arr);
        assert(result == 23);
        std::cerr << "test three passed\n";
    }
    {
        std::stringstream ss(
                "1 2 "
                "2 2 "
                "3 3 "
        );
        auto arr = ReadShips(3, ss);
        auto result = MinimumNumbersOfMoves(arr);
        assert(result == 1);
        std::cerr << "test four passed\n";
    }
    {
        std::stringstream ss(
                "1 1 "
                "2 2 "
                "3 3 "
        );
        auto arr = ReadShips(3, ss);
        auto result = MinimumNumbersOfMoves(arr);
        assert(result == 2);
        std::cerr << "test five passed\n";
    }
    {
        std::stringstream ss(
                "1 1 "
                "2 1 "
                "3 1 "
        );
        auto arr = ReadShips(3, ss);
        auto result = MinimumNumbersOfMoves(arr);
        assert(result == 0);
        std::cerr << "test six passed\n";
    }
}