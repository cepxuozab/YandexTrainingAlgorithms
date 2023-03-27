#include <iostream>
#include <string>

std::string perform()
{
    std::string str;
    getline(std::cin, str);
    std::string tmp;
    for (char ch : str) {
        if (ch == '+' || isdigit(ch) != 0) {
            tmp += ch;
        }
    }
    if (tmp.front() == '+') {
        tmp = tmp.substr(2);
        tmp = "8" + tmp;
    }
    if (tmp.size() == 7U) {
        tmp = "8495" + tmp;
    }
    return tmp;
}

int main()
{
    std::string one = perform(), two = perform(), three = perform(), four = perform();
    two == one ? puts("YES") : puts("NO");
    three == one ? puts("YES") : puts("NO");
    four == one ? puts("YES") : puts("NO");
}
