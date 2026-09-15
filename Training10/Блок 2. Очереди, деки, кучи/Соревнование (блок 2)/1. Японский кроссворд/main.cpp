#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace {

    using Clues = std::vector<int>;

    // Подсказка для одной линии: длины максимальных серий '#'
    // в порядке следования клеток.
    auto black_runs(const std::string& line) -> Clues {
        return line | std::views::chunk_by([](char lhs, char rhs)->bool { return lhs == rhs; })
                    | std::views::filter([](const auto& run)->bool { return run.front() == '#'; })
                    | std::views::transform([](const auto& run)->int { return static_cast<int>(run.size()); })
                    | std::ranges::to<Clues>();
    }

    void print_clues(const Clues& clues) {
        std::print("{}", clues.size());
        for (int clue : clues) {
            std::print(" {}", clue);
        }
        std::println();
    }

}  // namespace

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int height = 0;
    int width = 0;
    std::cin >> height >> width;

    std::vector<std::string> grid(height);
    for (std::string& row : grid) {
        std::cin >> row;
    }

    for (const std::string& row : grid) {
        print_clues(black_runs(row));
    }

    for (int col = 0; col < width; ++col) {
        std::string column =
            grid | std::views::transform([col](const std::string& row) -> auto { return row[col]; })
                 | std::ranges::to<std::string>();
        print_clues(black_runs(column));
    }
}