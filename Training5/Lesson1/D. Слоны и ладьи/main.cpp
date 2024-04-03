#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
int constexpr SIZE = 8;

auto Check(int r, int c, std::vector<std::string> const& matrix) -> bool {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && matrix[r][c] != 'R' && matrix[r][c] != 'B';
}
void Remove_obstacles(int row, int col, std::vector<std::string>& matrix,
                      std::vector<std::pair<int, int>> const& directions) {
    for (auto const& [dr, dc] : directions) {
        int r = row + dr;
        int c = col + dc;
        while (Check(r, c, matrix)) {
            if (matrix[r][c] == '*') {
                matrix[r][c] = '#';
            }
            r += dr, c += dc;
        }
    }
}

auto CountEmptyCells(std::vector<std::string>& matrix) {
    std::vector<std::pair<int, int>> const directions_rook = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::pair<int, int>> const directions_bishop = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (matrix[row][col] == 'R') {
                Remove_obstacles(row, col, matrix, directions_rook);
            } else if (matrix[row][col] == 'B') {
                Remove_obstacles(row, col, matrix, directions_bishop);
            }
        }
    }
    long long sum = 0;
    for (auto& str : matrix) {
        sum += std::ranges::count(str, '*');
    }
    return static_cast<int>(sum);
}

auto main() -> int {
    std::vector<std::string> matrix(SIZE);
    for (auto& str : matrix) {
        std::cin >> str;
    }
    std::cout << CountEmptyCells(matrix);
}