#include <iostream>
#include <string>
#include <vector>


int main() {
  std::vector<int> stack;
  for (std::string str; getline(std::cin, str);) {
    if (str == "exit") {
        std::cout<<"bye"<<'\n';
      break;
    }
    if (str == "clear") {
      stack.clear();
      std::cout << "ok" << '\n';
      continue;
    }
    if (str == "size") {
      std::cout << stack.size() << '\n';
      continue;
    }
    if (str == "back") {
      if (stack.empty()) {
        std::cout << "error" << '\n';
      } else {
        std::cout << stack.back() << '\n';
      }
      continue;
    }
    if (str == "pop") {
      if (stack.empty()) {
        std::cout << "error" << '\n';
      } else {
        std::cout << stack.back() << '\n';
        stack.pop_back();
      }
      continue;
    }
    auto pos = str.find(' ');
    if (pos == std::string::npos) {
      std::cout << "error" << '\n';
      continue;
    }
    std::string command = str.substr(0, pos);
    if (command != "push") {
      std::cout << "error" << '\n';
      continue;
    }
    std::string value = str.substr(pos + 1);
    try {
      int num = std::stoi(value);
      stack.push_back(num);
      std::cout << "ok" << '\n';
    } catch (const std::invalid_argument &e) {
      std::cout << "error" << '\n';
    } catch (const std::out_of_range &e) {
      std::cout << "error" << '\n';
    }
  }
}
