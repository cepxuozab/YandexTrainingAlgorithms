#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct Position {
    int min{};
    int max{};
};
auto Count(std::vector<std::string> const &square, Position &pos_i, Position &pos_j) -> int;

void Mark(std::vector<std::string> &square, int k, int l, int di, int dj);

auto main() -> int {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::string> square(m, std::string(n, ' '));
    for (int i = 0; i < m; ++i) {
        auto &curr = square[i];
        std::string str;
        std::cin >> str;
        for (int j = 0; j < n; ++j) {
            curr[j] = str[j] == '#' ? '1' : '0';
        }
    }
    Position pos_i, pos_j;
    int cnt = Count(square, pos_i, pos_j);
    if (cnt < 2) {
        printf("NO\n");
        return 0;
    }
    if (square[pos_i.min][pos_j.min] != '0')
        Mark(square, pos_i.min, pos_j.min, 1, 1);
    else if (square[pos_i.max][pos_j.min] != '0')
        Mark(square, pos_i.max, pos_j.min, -1, 1);
    else if (square[pos_i.min][pos_j.max] != '0')
        Mark(square, pos_i.min, pos_j.max, 1, -1);
    else if (square[pos_i.max][pos_j.max] != '0')
        Mark(square, pos_i.max, pos_j.max, -1, -1);
    else {
        printf("NO\n");
        return 0;
    }
    if (int f = Count(square, pos_i, pos_j); f == 0) {
        if (pos_i.min < pos_i.max) {
            for (int j = pos_j.min; j <= pos_j.max; ++j) {
                square[pos_i.max][j] = '1';
            }
        } else {
            square[pos_i.min][pos_j.max] = '1';
        }
    } else if (f != (pos_i.max - pos_i.min + 1) * (pos_j.max - pos_j.min + 1)) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = square[i][j] - '0';
            putchar(".ab"[idx]);
        }
        putchar('\n');
    }
}

void Mark(std::vector<std::string> &square, int k, int l, int di, int dj) {
    int m = static_cast<int>(square.size());
    int n = static_cast<int>(square.front().size());

    for (int i = k; i >= 0 && i < m; i += di)
        for (int j = l; j >= 0 && j < n && square[k][j] != '0'; j += dj)
            if (square[i][j] == '1')
                square[i][j] = '2';
            else {
                for (j = l; j >= 0 && j < n && square[k][j] != '0' && square[i][j] != '0'; j += dj)
                    square[i][j] = '1';
                return;
            }
}

auto Count(std::vector<std::string> const &square, Position &pos_i, Position &pos_j) -> int {
    int cnt = 0;
    int m = static_cast<int>(square.size());
    int n = static_cast<int>(square.front().size());
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (square[i][j] == '1') {
                if (cnt == 0) {
                    pos_i = {i, i};
                    pos_j = {j, j};
                } else {
                    if (pos_i.min > i) {
                        pos_i.min = i;
                    }
                    if (pos_i.max < i) {
                        pos_i.max = i;
                    }
                    if (pos_j.min > j) {
                        pos_j.min = j;
                    }
                    if (pos_j.max < j) {
                        pos_j.max = j;
                    }
                }
                cnt++;
            }
        }
    }
    return cnt;
}
