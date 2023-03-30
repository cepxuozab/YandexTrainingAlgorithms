#include <algorithm>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_map>

auto main() -> int
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::unordered_map<std::string, int> dict;
    for (std::string word; input >> word;) {
        dict[word]++;
    }
    using Pair = std::pair<std::string const, int> const&;
    auto compare = [&](Pair lhs, Pair rhs) {
        return dict.at(lhs.first) == dict.at(rhs.first)
            ? lhs.first > rhs.first
            : dict.at(lhs.first) < dict.at(rhs.first);
    };
    auto result = std::ranges::max_element(dict, compare);
    output << result->first << '\n';

    return 0;
}
