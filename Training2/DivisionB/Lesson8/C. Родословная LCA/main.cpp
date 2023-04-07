#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

std::vector<std::string> Ancestors(std::unordered_map<std::string, std::string> const& dict, std::string child)
{
    std::vector<std::string> result{ child };
    while (dict.contains(child)) {
        child = dict.at(child);
        result.push_back(child);
    }
    return result;
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
        auto ones = Ancestors(dict, one);
        std::unordered_set ancestors_for_1(ones.begin(), ones.end());
        for (auto const& ancestor : Ancestors(dict, two)) {
            if (ancestors_for_1.contains(ancestor)) {
                std::cout << ancestor << '\n';
                break;
            }
        }
    }
    return 0;
}
