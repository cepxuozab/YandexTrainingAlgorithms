#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  int cntLt = 0, cntGt = 0, cntSlash = 0;
  std::array<int, 26> cntLetter{};

  for (char c : s) {
    if (c == '<')
      ++cntLt;
    else if (c == '>')
      ++cntGt;
    else if (c == '/')
      ++cntSlash;
    else if (c >= 'a' && c <= 'z')
      ++cntLetter[c - 'a'];
  }

  if (cntLt != cntGt || cntLt % 2 != 0) {
    std::cout << "Impossible\n";
    return 0;
  }

  int n = cntLt / 2;
  if (cntSlash != n) {
    std::cout << "Impossible\n";
    return 0;
  }

  for (int i = 0; i < 26; ++i)
    if (cntLetter[i] % 2 != 0) {
      std::cout << "Impossible\n";
      return 0;
    }

  int T = 0;
  for (int i = 0; i < 26; ++i)
    T += cntLetter[i];

  if (n == 0) {
    if (T != 0) {
      std::cout << "Impossible\n";
      return 0;
    }
    std::cout << "\n";
    return 0;
  }
  if (T / 2 < n) {
    std::cout << "Impossible\n";
    return 0;
  }

  std::string pool;
  pool.reserve(T / 2);
  for (int i = 0; i < 26; ++i)
    pool.append(cntLetter[i] / 2, static_cast<char>('a' + i));

  std::vector<std::string> names(n);
  int idx = 0;
  for (int i = 0; i < n - 1; ++i)
    names[i] = pool.substr(idx++, 1);
  names[n - 1] = pool.substr(idx);

  std::stack<std::string> st;
  std::string result;
  result.reserve(s.size());

  for (auto &name : names) {
    result += '<';
    result += name;
    result += '>';
    st.push(name);
  }
  while (!st.empty()) {
    result += "</";
    result += st.top();
    result += '>';
    st.pop();
  }

  std::cout << result << "\n";
  return 0;
}