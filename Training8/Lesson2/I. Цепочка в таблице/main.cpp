#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  vector<vector<int>> a;
  vector<vector<int>> dp;

  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};
  cin >> n >> m;
  a.assign(n, vector<int>(m, 0));
  dp.assign(n, vector<int>(m, -1));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];

  auto dfs = [&](auto &&self, int x, int y) {
    if (dp[x][y] != -1)
      return dp[x][y];

    int best = 1; // минимум длина 1 — сама клетка

    for (int dir = 0; dir < 4; ++dir) {
      int nx = x + dx[dir];
      int ny = y + dy[dir];
      if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        if (a[nx][ny] == a[x][y] + 1) {
          best = max(best, 1 + self(self, nx, ny));
        }
      }
    }

    return dp[x][y] = best;
  };
  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      ans = max(ans, dfs(dfs, i, j));

  cout << ans << "\n";
  return 0;
}
