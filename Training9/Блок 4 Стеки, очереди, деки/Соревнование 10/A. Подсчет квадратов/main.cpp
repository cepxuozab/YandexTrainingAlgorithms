#include <iostream>
#include <vector>
#include <queue>

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> grid[i];
    }

    std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
    int result = 0;

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (grid[i][j] == '#' && !used[i][j])
            {
                std::queue<std::pair<int, int>> q;
                q.emplace(i, j);
                used[i][j] = true;

                int min_r = i, max_r = i;
                int min_c = j, max_c = j;
                int count = 0;

                while (!q.empty())
                {
                    auto [r, c] = q.front();
                    q.pop();
                    ++count;

                    min_r = std::min(min_r, r);
                    max_r = std::max(max_r, r);
                    min_c = std::min(min_c, c);
                    max_c = std::max(max_c, c);

                    for (int k = 0; k < 4; ++k)
                    {
                        int nr = r + dr[k];
                        int nc = c + dc[k];

                        if (nr >= 0 && nr < n && nc >= 0 && nc < m)
                        {
                            if (grid[nr][nc] == '#' && !used[nr][nc])
                            {
                                used[nr][nc] = true;
                                q.emplace(nr, nc);
                            }
                        }
                    }
                }

                int height = max_r - min_r + 1;
                int width = max_c - min_c + 1;

                if (height == width && count == height * width)
                {
                    ++result;
                }
            }
        }
    }

    std::cout << result << "\n";
    return 0;
}
