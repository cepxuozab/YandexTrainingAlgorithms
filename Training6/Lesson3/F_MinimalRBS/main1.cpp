#include <iostream>
#include <map>
#include <stack>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::string prior;
  std::cin >> prior;
  std::map<char, int> priority;
  for (size_t i = 0; i < prior.size(); ++i) {
    priority[prior[i]] = i;
  }
  std::map<char, char> pairs{{'(', ')'}, {'[', ']'}};
  std::string ans;
  std::cin >> ans;
  std::stack<char> stack;
  for (char ch : ans) {
    if (pairs.contains(ch)) {
      stack.push(ch);
    } else {
      if (!stack.empty()) {
        stack.pop();
      }
    }
  }
  int extra_length = (n - std::size(ans) - std::size(stack)) / 2;
  while (!stack.empty() || extra_length != 0) {
    if (!stack.empty() && (priority[pairs[stack.top()]] < priority['('] &&
                               priority[pairs[stack.top()]] < priority['['] ||
                           extra_length == 0)) {
      ans += pairs[stack.top()];
      stack.pop();
    }

    else {
      char ch = priority['('] < priority['['] ? '(' : '[';
      stack.push(ch);
      ans += ch;
      extra_length--;
    }
  }
  std::cout << ans;
}
