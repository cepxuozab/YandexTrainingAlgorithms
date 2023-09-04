#include <iostream>
#include <queue>
#include <vector>

struct Pos {
    int i_ {};
    int j_ {};
    Pos(int i, int j)
        : i_(i)
        , j_(j)
    {
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    int sizeI, sizeJ;
    std::cin >> sizeI >> sizeJ;
    std::vector<std::vector<int>> a(sizeI + 1 + 1, std::vector<int>(sizeJ + 1 + 1, 1));
    for (int i = 1; i <= sizeI; ++i) {
        for (int j = 1; j <= sizeJ; ++j) {
            std::cin >> a[i][j];
        }
    }
    const int UNDEF = -1;
    std::vector<std::vector<int>> len(sizeI + 1 + 1, std::vector<int>(sizeJ + 1 + 1, UNDEF));
    len[1][1] = 0;
    std::queue<Pos> points;
    points.push(Pos(1, 1));
    while (!points.empty()) {
        auto cur = points.front();
        points.pop();
        if (a[cur.i_][cur.j_] == 2) {

            printf("%d", len[cur.i_][cur.j_]);
            return 0;
        }
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di * di + dj * dj == 1) {
                    int ni = cur.i_;
                    int nj = cur.j_;
                    while (true) {
                        if (a[ni][nj] == 2) {
                            break;
                        }
                        if (a[ni + di][nj + dj] == 1) {
                            break;
                        }
                        ni += di;
                        nj += dj;
                    }
                    int& prev = len[ni][nj];
                    if (prev == UNDEF) {
                        prev = len[cur.i_][cur.j_] + 1;
                        points.push(Pos(ni, nj));
                    }
                }
            }
        }
    }
}
