#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

struct Interval {
  double begin, end, weight;

  bool operator<(const Interval &other) const { return end < other.end; }
};

// Бинарный поиск последнего интервала j: intervals[j].end <= intervals[i].begin
int findLastNonOverlapping(const vector<Interval> &intervals, int i) {
  int left = 0, right = i - 1, result = -1;

  while (left <= right) {
    int mid = (left + right) / 2;
    if (intervals[mid].end <= intervals[i].begin) {
      result = mid;
      left = mid + 1; // Ищем правее
    } else {
      right = mid - 1; // Ищем левее
    }
  }

  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n == 0) {
    cout << 0.0 << '\n';
    return 0;
  }

  vector<Interval> intervals(n);
  for (int i = 0; i < n; i++) {
    cin >> intervals[i].begin >> intervals[i].end >> intervals[i].weight;
  }

  // Сортируем по времени окончания
  sort(intervals.begin(), intervals.end());

  // dp[i] = максимальный вес, используя интервалы 0..i
  vector<double> dp(n);
  dp[0] = intervals[0].weight;

  for (int i = 1; i < n; i++) {
    // Вариант 1: не берем i-й интервал
    double without = dp[i - 1];

    // Вариант 2: берем i-й интервал
    double with = intervals[i].weight;

    // Бинарным поиском находим последний непересекающийся интервал
    int j = findLastNonOverlapping(intervals, i);

    if (j >= 0) {
      with += dp[j];
    }

    dp[i] = max(without, with);
  }

  cout << dp[n - 1] << '\n';

  return 0;
}