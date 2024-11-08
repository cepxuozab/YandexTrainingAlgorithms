#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class StackSum {
    std::vector<int> data;
    std::vector<int64_t> prefix = std::vector<int64_t>(1, 0);

public:
    auto Pop() -> int {
        auto res = data.back();
        data.pop_back();
        prefix.pop_back();
        return res;
    }

    void Push(int val) {
        data.push_back(val);
        prefix.push_back(prefix.back() + val);
    }

    auto Sum(int k) -> int64_t {
        size_t idx = prefix.size() - 1 - k;
        return prefix.back() - prefix[idx];
    }
};

auto main() -> int {  // NOLINT
    StackSum stack;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;
        char operation = command.front();
        switch (operation) {
            case '-':
                std::cout << stack.Pop() << '\n';
                break;
            case '+':
                stack.Push(stoi(command.substr(1)));
                break;
            case '?':
                std::cout << stack.Sum(stoi(command.substr(1))) << '\n';
                break;
            default:
                throw std::invalid_argument("wrong command");
        }
    }
}