#include <array>
#include <iostream>

constexpr int SIZE = 10;

int main() {
    int n;
    std::cin >> n;
    std::array<std::array<short, SIZE>, SIZE> board{};
    for (auto &arr: board) {
        arr.fill(1);
    }
    for (int i = 0; i < n; ++i) {
        int y, x;
        std::cin >> y >> x;
        board[y][x] = 0;
    }
    int perimeter = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                perimeter += (board[i - 1][j] + board[i + 1][j] + board[i][j - 1] + board[i][j + 1]);
            }
        }
    }
    std::cout << perimeter;
}
