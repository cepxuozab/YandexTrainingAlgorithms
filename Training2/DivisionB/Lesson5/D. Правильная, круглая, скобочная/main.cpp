#include <iostream>
#include <stack>
#include <string>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    std::string str;
    getline(std::cin, str);
    std::stack<char> stack;
    for (char ch : str) {
        if (ch == '(') {
            stack.push(')');
        }
        else {
            if (stack.empty() || stack.top() != ch) {
                puts("NO");
                return 0;
            }
            stack.pop();
        }
    }
    stack.empty() ? puts("YES") : puts("NO");
    return 0;
}
