#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

auto main() -> int
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::unordered_map<std::string, std::unordered_set<std::string>> dict;
    unsigned n;
    input >> n;
    input.ignore(INT_MAX, '\n');
    for (unsigned i = 0; i < n; ++i) {
        std::string word;
        getline(input, word);
        if (std::ranges::count_if(word, isupper) == 1) {
            std::string tmp;
            std::ranges::transform(word, std::back_inserter(tmp), tolower);
            dict[tmp].insert(word);
        }
    }
    std::string request;
    getline(input, request);
    int ans = 0;
    auto check = [&](auto const& view) {
        std::string one;
        for (const auto element : view)
            one += element;
        std::string tmp;
        std::ranges::transform(one, std::back_inserter(tmp), tolower);
        auto it = dict.find(tmp);
        if (it == dict.end()) {
            if (std::ranges::count_if(one, isupper) != 1)
                ans++;
        } else {
            auto const& sets = dict.at(tmp);
            ans += (sets.find(one) != sets.end() ? 0 : 1);
        }
    };
    std::ranges::for_each(request | std::ranges::views::split(' '), check);
    output << ans << '\n';
    return 0;
}
