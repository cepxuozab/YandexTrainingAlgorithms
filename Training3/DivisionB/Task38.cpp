#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

std::vector<std::pair<int, int>> getNeighbours(int x, int y, int n, int m)
{
    std::vector<std::pair<int, int>> dir {
        { x - 2, y - 1 }, { x - 2, y + 1 }, { x - 1, y - 2 }, { x - 1, y + 2 },
        { x + 1, y - 2 }, { x + 1, y + 2 }, { x + 2, y - 1 }, { x + 2, y + 1 }
    };
    std::vector<std::pair<int, int>> Neighbours;
    for (auto const& [a, b] : dir) {
        if (a >= 0 && a < n && b >= 0 && b < m) {
            Neighbours.emplace_back(a, b);
        }
    }
    return Neighbours;
}
int main()
{
    if (freopen("input.txt", "r", stdin) == 0) {
        puts("Can't open input.txt");
        return 0;
    }
    int n, m, s, t, q;
    std::cin >> n >> m >> s >> t >> q;
    s--;
    t--;
    std::vector<std::vector<int>> mat(n, std::vector<int>(m, -1));
    mat[s][t] = 0;
    std::vector<std::pair<int, int>> dist { { s, t } }, currr_dist;
    int cur = 0, ma = 0;
    while (cur <= ma) {
        for (auto const& [x, y] : dist) {
            for (auto const& next : getNeighbours(x, y, n, m)) {
                if (mat[next.first][next.second] == -1) {
                    mat[next.first][next.second] = cur + 1;
                    currr_dist.push_back(next);
                    ma = cur + 1;
                }
            }
        }
        dist.swap(currr_dist);
        currr_dist.clear();
        cur++;
    }
    int ans = 0;
    bool flag = true;
    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        if (mat[a][b] == -1) {
            flag = false;
        }
        ans += mat[a][b];
    }
    if (!flag)
        ans = -1;
    std::cout << ans << std::endl;
    return 0;
}
