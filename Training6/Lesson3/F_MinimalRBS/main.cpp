#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

void pushInSt(stack<char>& st, char symbol) {
    if (!st.empty() && ((st.top() == '(' && symbol == ')') || (st.top() == '[' && symbol == ']')))
        st.pop();
    else
        st.push(symbol);
}

auto main() -> int {  // NOLINT
    int n;
    string order;
    string inp;
    stack<char> st;
    int openParen = 0;
    int closeParen = 0;
    int openSqu = 0;
    int closeSqu = 0;
    cin >> n;
    cin >> order;
    cin >> inp;
    for (auto ch : inp) {
        if (ch == '[')
            openSqu++;
        else if (ch == ']')
            closeSqu++;
        else if (ch == '(')
            openParen++;
        else
            closeParen++;
        pushInSt(st, ch);
    }
    while ((openParen + openSqu + closeSqu + closeParen) != n) {
        for (int i = 0; i < 4; i++) {
            if (order[i] == '(') {
                if (openSqu + openParen < n / 2) {
                    pushInSt(st, '(');
                    inp += '(';
                    openParen++;
                    break;
                }
            } else if (order[i] == ')') {
                if (!st.empty() && st.top() == '(') {
                    pushInSt(st, ')');
                    inp += ')';
                    closeParen++;
                    break;
                }
            } else if (order[i] == '[') {
                if (openSqu + openParen < n / 2) {
                    pushInSt(st, '[');
                    inp += '[';
                    openSqu++;
                    break;
                }
            } else {
                if (!st.empty() && st.top() == '[') {
                    pushInSt(st, ']');
                    inp += ']';
                    closeSqu++;
                    break;
                }
            }
        }
    }
    cout << inp << '\n';
}