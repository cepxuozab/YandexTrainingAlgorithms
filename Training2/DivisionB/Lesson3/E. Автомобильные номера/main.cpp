#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

[[maybe_unused]] static auto const FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        throw std::invalid_argument("can'n read");
    }
    int m;
    std::cin >> m;
    std::vector<std::string> witnesses(m);
    for (auto& witness : witnesses) {
        std::cin >> witness;
    }
    int n;
    std::cin >> n;
    std::vector<std::string> numbers(n);
    for (auto& number : numbers) {
        std::cin >> number;
    }
    std::unordered_map<std::string, std::unordered_set<int>> dict;
    size_t maximum = 0;
    for (auto const& number : numbers) {
        std::unordered_set<char> num(number.begin(), number.end());
        for (size_t i = 0; i < witnesses.size(); ++i) {
            std::unordered_set<char> witness(witnesses[i].begin(), witnesses[i].end());
            bool flag = true;
            for (char ch : witness) {
                flag = flag && num.contains(ch);
            }
            if (flag) {
                dict[number].insert(i);
            }
        }
        maximum = maximum > dict[number].size() ? maximum : dict[number].size();
    }
    for (auto const& number : numbers) {
        if (dict[number].size() == maximum) {
            std::cout << number << '\n';
        }
    }
    return 0;
}
