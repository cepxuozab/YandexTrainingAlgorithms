#include <iostream>
#include <stack>
#include <string>
#include <string_view>

auto CorrectBracketSequence(std::string_view str) -> std::string;

auto main() -> int  // NOLINT
{
    std::string str;
    std::cin >> str;
    std::cout << CorrectBracketSequence(str) << '\n';
    return 0;
}

auto CorrectBracketSequence(std::string_view str) -> std::string {
    std::stack<char> stack;
    for (char ch : str) {
        switch (ch) {
            case '[':
                stack.push(']');
                break;
            case '{':
                stack.push('}');
                break;
            case '(':
                stack.push(')');
                break;
            default:
                if (stack.empty() || stack.top() != ch) {
                    return "no";
                }
                stack.pop();
                break;
        }
    }
    return (stack.empty() ? "yes" : "no");
}