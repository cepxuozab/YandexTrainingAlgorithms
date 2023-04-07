#include <iostream>
#include <string>
#include <unordered_map>

int Parent(std::unordered_map<std::string, std::string> const& dict, std::string a1, std::string a2)
{
    std::string s(a1);
    while (dict.contains(s)) {
        s = dict.at(s);
        if (s == a2) {
            return 2;
        }
    }
    s = a2;
    while (dict.contains(s)) {
        s = dict.at(s);
        if (s == a1) {
            return 1;
        }
    }
    return 0;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::unordered_map<std::string, std::string> dict;
    for (int i = 0; i < n - 1; ++i) {
        std::string child, parent;
        std::cin >> child >> parent;
        dict[child] = parent;
    }
    std::string one, two;
    while (std::cin >> one >> two) {
        std::cout << Parent(dict, one, two) << ' ';
    }
    std::cout << '\n';
    return 0;
}
