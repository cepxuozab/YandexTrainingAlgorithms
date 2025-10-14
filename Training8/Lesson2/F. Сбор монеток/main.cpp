#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>


using namespace std;

const int NEG_INF = -10000000; // -10^7 is enough (n <= 10000)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<char>> grid(n, vector<char>(3));
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < 3; ++j) {
      grid[i][j] = s[j];
    }
  }

  vector<int> dp(3, NEG_INF);
  int global_ans = 0;

  // First row
  bool possible = false;
  for (int c = 0; c < 3; ++c) {
    if (grid[0][c] == 'W') {
      dp[c] = NEG_INF;
    } else {
      dp[c] = (grid[0][c] == 'C' ? 1 : 0);
      possible = true;
      global_ans = max(global_ans, dp[c]);
    }
  }

  if (!possible) {
    cout << 0 << '\n';
    return 0;
  }

  // Rows 1 to n-1
  for (int r = 1; r < n; ++r) {
    vector<int> new_dp(3, NEG_INF);
    bool row_possible = false;
    for (int c = 0; c < 3; ++c) {
      if (grid[r][c] == 'W') {
        new_dp[c] = NEG_INF;
        continue;
      }

      int best_prev = NEG_INF;
      for (int dc = -1; dc <= 1; ++dc) {
        int prev_c = c + dc;
        if (prev_c >= 0 && prev_c < 3) {
          if (dp[prev_c] != NEG_INF) {
            best_prev = max(best_prev, dp[prev_c]);
          }
        }
      }

      if (best_prev != NEG_INF) {
        new_dp[c] = best_prev + (grid[r][c] == 'C' ? 1 : 0);
        global_ans = max(global_ans, new_dp[c]);
        row_possible = true;
      }
      // else remains NEG_INF
    }
    dp = move(new_dp);
    // Even if row not possible, we keep global_ans from previous rows
  }

  cout << global_ans << '\n';
  return 0;
}