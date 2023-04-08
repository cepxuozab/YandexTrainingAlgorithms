#include <functional>
#include <iostream>
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
    std::string expression;
    getline(std::cin, expression);
    while (!expression.empty() && expression.back() == ' ') {
        expression.pop_back();
    }
    std::istringstream input(expression);
    std::stack<int> stack;
    for (std::string str; input >> str;) {
        if (str == "*") {
            Operate(stack, std::multiplies<int>());
        } else if (str == "+") {
            Operate(stack, std::plus<int>());
        } else if (str == "-") {
            Operate(stack, std::minus<int>());
        } else {
            stack.push(std::stoi(str));
        }
    }
    std::cout << stack.top() << std::endl;
    return 0;
}
