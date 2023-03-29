#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::string one, two;
    getline(input, one);
    getline(input, two);
    std::unordered_set<std::string> genom;
    for (size_t i = 0; i + 2 <= two.size(); ++i) {
        genom.insert(two.substr(i, 2));
    }
    int ans = 0;
    for (size_t i = 0; i + 2 <= one.size(); ++i) {
        ans += genom.count(one.substr(i, 2));
    }
    std::cout << ans;
}
