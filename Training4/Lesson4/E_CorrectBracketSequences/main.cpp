#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int n;
stack<char> s;
string opened = "([";
string closed = ")]";
string res;
void input()
{
    cin >> n;
    res.resize(n);
}
char GetPair(char openBracket)
{
    int pos = opened.find(openBracket);
    return closed[pos];
}
void rec(int pos, int openBracketsAmount)
{
    if (pos == n) {
        printf("%s\n", res.c_str());
        return;
    }
    // если можем еще открывать скобки - делаем это
    if (n - 1 - pos > openBracketsAmount) {
        for (int i = 0; i < opened.size(); i++) {
            res[pos] = opened[i];
            s.push(opened[i]);

            rec(pos + 1, openBracketsAmount + 1);

            s.pop();
        }
    }
    // если есть что закрывать - делаем это
    if (!s.empty()) {
        char curOpen = s.top();
        res[pos] = GetPair(curOpen);
        s.pop();

        rec(pos + 1, openBracketsAmount - 1);

        s.push(curOpen);
    }
}
void solve()
{
    rec(0, 0);
}
int main()
{
    input();
    solve();
    return 0;
}
