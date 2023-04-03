#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

int main()
{
    std::string first;
    std::string second;
    getline(std::cin, first);
    getline(std::cin, second);
    const std::string delim{ " " };
    std::unordered_map<std::string, int> first_freq, second_freq;
    for (auto const word : std::ranges::views::split(first, delim)) {
        first_freq[{ word.begin(), word.end() }]++;
    }
    for (auto const word : std::ranges::views::split(second, delim)) {
        second_freq[{ word.begin(), word.end() }]++;
    }
    int res = 0;
    for (auto const& [num, val] : first_freq) {
        if (auto it = second_freq.find(num); it != second_freq.end()) {
            res += std::min(val, it->second);
        }
    }
    std::cout << res;
    return 0;
}
