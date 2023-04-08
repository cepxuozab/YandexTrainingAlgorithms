#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
template <typename Func>
void Operate(std::stack<int>& stack, Func operation)
{
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    stack.push(operation(b, a));
}

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input file");
        return 1;
    }
    std::map<std::string, std::function<int(int, int)>> ops {
        { "*", std::multiplies<>() }, { "-", std::minus<>() }, { "+", std::plus<>() }
    };
    std::stack<int> stack;
    for (std::string data; std::cin >> data;) {
        if (data.empty()) {
            continue;
        }
        if (auto it = ops.find(data); it != ops.end()) {
            Operate(stack, it->second);
        } else {
            stack.push(std::stoi(data));
        }
    }
    std::cout << stack.top() << std::endl;
    return 0;
}
