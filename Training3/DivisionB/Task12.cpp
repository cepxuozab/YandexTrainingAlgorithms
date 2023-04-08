#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::string line;
    std::cin >> line;

    bool result = true;
    std::stack<char> sequence;

    for (char symb : line) {
        if (symb == '(' || symb == '[' || symb == '{') {
            sequence.push(symb);
        } else {
            if (sequence.empty()) {
                result = false;
                break;
            } else {
                if (symb == ')' && sequence.top() == '(') {
                    sequence.pop();
                } else if (symb == ']' && sequence.top() == '[') {
                    sequence.pop();
                } else if (symb == '}' && sequence.top() == '{') {
                    sequence.pop();
                } else {
                    result = false;
                    break;
                }
            }
        }
    }

    if ((result && sequence.empty()) || line == "" || line == " ")
        std::cout << "yes\n";
    else
        std::cout << "no\n";
    return 0;
}
