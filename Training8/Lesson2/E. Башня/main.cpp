#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>


using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, K;
  cin >> N >> K;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  // Предвычислим score для каждой башни
  vector<long long> score(N - K + 1, 0);
  for (int i = 0; i <= N - K; ++i) {
    long long sum = 0;
    int min_val = INT_MAX;
    for (int j = 0; j < K; ++j) {
      sum += A[i + j];
      min_val = min(min_val, A[i + j]);
    }
    score[i] = sum * min_val;
  }

  vector<long long> dp(N + 1, 0);
  vector<bool> take(
      N + 1, false); // take[i] = true, если взяли башню, заканчивающуюся в i-1

  for (int i = 1; i <= N; ++i) {
    // Вариант: не брать башню, заканчивающуюся в i-1
    dp[i] = dp[i - 1];
    take[i] = false;

    // Вариант: взять башню, начинающуюся в i-K
    if (i >= K) {
      long long candidate = dp[i - K] + score[i - K];
      if (candidate > dp[i]) {
        dp[i] = candidate;
        take[i] = true;
      }
    }
  }

  // Восстановление
  vector<int> towers;
  int pos = N;
  while (pos > 0) {
    if (take[pos]) {
      towers.push_back(pos - K + 1); // номер с 1
      pos -= K;
    } else {
      pos -= 1;
    }
  }

  reverse(towers.begin(), towers.end());

  cout << towers.size() << '\n';
  for (size_t i = 0; i < towers.size(); ++i) {
    if (i > 0)
      cout << ' ';
    cout << towers[i];
  }
  cout << '\n';

  return 0;
}