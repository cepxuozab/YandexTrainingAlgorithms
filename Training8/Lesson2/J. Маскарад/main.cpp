#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, L;
  cin >> N >> L;

  struct Shop {
    int P, R, Q, F;
  };

  vector<Shop> shops(N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> shops[i].P >> shops[i].R >> shops[i].Q >> shops[i].F;
  }

  // Максимум ткани, которую вообще можно купить
  int maxL = 0;
  for (auto &s : shops)
    maxL += s.F;
  if (maxL < L) {
    cout << -1 << "\n";
    return 0;
  }

  vector<vector<int>> dp(N + 1, vector<int>(maxL + 1, INF));
  vector<vector<int>> choice(N + 1, vector<int>(maxL + 1, -1));

  dp[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    auto [P, R, Q, F] = shops[i];
    for (int prev = 0; prev <= maxL; prev++) {
      if (dp[i - 1][prev] == INF)
        continue;

      for (int x = 0; x <= F; x++) {
        int cost = (x >= R ? x * Q : x * P);
        int nxt = min(maxL, prev + x);
        if (dp[i][nxt] > dp[i - 1][prev] + cost) {
          dp[i][nxt] = dp[i - 1][prev] + cost;
          choice[i][nxt] = x;
        }
      }
    }
  }

  // ищем минимальную стоимость для l >= L
  int bestL = -1;
  int bestCost = INF;
  for (int l = L; l <= maxL; l++) {
    if (dp[N][l] < bestCost) {
      bestCost = dp[N][l];
      bestL = l;
    }
  }

  if (bestL == -1) {
    cout << -1 << "\n";
    return 0;
  }

  cout << bestCost << "\n";

  // Восстановим решение
  vector<int> res(N + 1, 0);
  int l = bestL;
  for (int i = N; i >= 1; i--) {
    int x = choice[i][l];
    res[i] = x;
    l -= x;
    if (l < 0)
      l = 0;
  }

  for (int i = 1; i <= N; i++)
    cout << res[i] << (i == N ? '\n' : ' ');

  return 0;
}
