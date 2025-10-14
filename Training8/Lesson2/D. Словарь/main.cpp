#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>


using namespace std;

int main() {
  string s;
  getline(cin, s);

  string n_line;
  getline(cin, n_line);
  int N = stoi(n_line);

  unordered_set<string> dict;
  for (int i = 0; i < N; ++i) {
    string word;
    getline(cin, word);
    dict.insert(word);
  }

  int n = s.size();
  vector<bool> dp(n + 1, false);
  vector<int> prev(n + 1, -1);

  dp[0] = true;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (dp[j]) {
        string substr = s.substr(j, i - j);
        if (dict.count(substr)) {
          dp[i] = true;
          prev[i] = j;
          break; // достаточно одного разбиения
        }
      }
    }
  }

  // Восстановление ответа
  vector<string> words;
  int pos = n;
  while (pos > 0) {
    int p = prev[pos];
    words.push_back(s.substr(p, pos - p));
    pos = p;
  }

  reverse(words.begin(), words.end());

  for (size_t i = 0; i < words.size(); ++i) {
    if (i > 0)
      cout << " ";
    cout << words[i];
  }
  cout << endl;

  return 0;
}