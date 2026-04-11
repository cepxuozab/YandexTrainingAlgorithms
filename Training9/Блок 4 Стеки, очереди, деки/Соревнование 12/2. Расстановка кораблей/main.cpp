#include <iostream>
#include <vector>
#include <string>

auto main() -> int {
    constexpr int N = 10;
    std::vector<std::string> grid(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> grid[i];
    }

    std::vector<std::vector<bool>> used(N, std::vector<bool>(N, false));
    std::vector<int> ships(5, 0); // ships[size]

    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};

    auto inside = [&](int x, int y) -> bool {
        return x >= 0 && x < N && y >= 0 && y < N;
    };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == '#' && !used[i][j]) {
                int len = 0;

                // Определяем направление
                bool right = (j + 1 < N && grid[i][j + 1] == '#');
                bool down = (i + 1 < N && grid[i + 1][j] == '#');

                if (right && down) {
                    std::cout << "NO";
                    return 0;
                }

                int x = i, y = j;

                if (right) {
                    while (y < N && grid[x][y] == '#') {
                        if (used[x][y]) break;

                        // проверка окружения
                        for (int d = 0; d < 8; ++d) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];
                            if (inside(nx, ny) && grid[nx][ny] == '#' && !used[nx][ny]) {
                                if (!(nx == x && ny == y)) {
                                    if (!(nx == x && (ny == y - 1 || ny == y + 1))) {
                                        std::cout << "NO";
                                        return 0;
                                    }
                                }
                            }
                        }

                        used[x][y] = true;
                        ++len;
                        ++y;
                    }
                } else if (down) {
                    while (x < N && grid[x][y] == '#') {
                        if (used[x][y]) break;

                        for (int d = 0; d < 8; ++d) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];
                            if (inside(nx, ny) && grid[nx][ny] == '#' && !used[nx][ny]) {
                                if (!(nx == x && ny == y)) {
                                    if (!((ny == y) && (nx == x - 1 || nx == x + 1))) {
                                        std::cout << "NO";
                                        return 0;
                                    }
                                }
                            }
                        }

                        used[x][y] = true;
                        ++len;
                        ++x;
                    }
                } else {
                    // одиночная клетка
                    for (int d = 0; d < 8; ++d) {
                        int nx = i + dx[d];
                        int ny = j + dy[d];
                        if (inside(nx, ny) && grid[nx][ny] == '#') {
                            std::cout << "NO";
                            return 0;
                        }
                    }
                    used[i][j] = true;
                    len = 1;
                }

                if (len < 1 || len > 4) {
                    std::cout << "NO";
                    return 0;
                }

                ships[len]++;
            }
        }
    }

    if (ships[1] == 4 && ships[2] == 3 && ships[3] == 2 && ships[4] == 1) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}