#include <iostream>
#include <vector>
#include <string>

constexpr int SIZE = 10;

auto ReadBoards(int n) -> std::vector<std::string> {
    std::vector<std::string> chess_board(SIZE, std::string(SIZE, ' '));
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        chess_board[x][y] = '1';
    }
    return chess_board;
}

auto NeighbourCut(std::vector<std::string> const &chess_board, int x, int y) -> int {
    int count = 0;
    std::vector<std::pair<int, int>> diff{{-1, 0},
                                          {0,  -1},
                                          {0,  1},
                                          {1,  0}};
    for (auto &[dx, dy]: diff) {
        count += (chess_board[x + dx][y + dy] == ' ');
    }
    return count;
}

auto PerimeterCut(std::vector<std::string> const &chess_board) -> int {
    int perimeter = 0;
    for (int x = 0; x < SIZE; ++x) {
        auto const &line = chess_board[x];
        for (int y = 0; y < SIZE; ++y) {
            if (line[y] == '1') {
                perimeter += NeighbourCut(chess_board, x, y);
            }
        }
    }
    return perimeter;
}

auto main() -> int {
    int n;
    std::cin >> n;
    std::cout << PerimeterCut(ReadBoards(n));
}