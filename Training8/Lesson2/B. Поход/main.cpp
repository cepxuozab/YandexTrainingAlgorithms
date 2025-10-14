#include <algorithm>
#include <climits>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  getline(cin, s);

  const int INF = 1000000;
  int left = 0;    // after processing previous tributaries, on left bank
  int right = INF; // on right bank

  for (char c : s) {
    int cost_left = (c == 'L' || c == 'B') ? 1 : 0;
    int cost_right = (c == 'R' || c == 'B') ? 1 : 0;

    int new_left = min(left + cost_left, right + 1 + cost_left);
    int new_right = min(right + cost_right, left + 1 + cost_right);

    left = new_left;
    right = new_right;
  }

  int answer = min(right, left + 1);
  cout << answer << '\n';
  return 0;
}