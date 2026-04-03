#include <iostream>
#include <string>
#include <unordered_map>

auto countBalancedSubsegments(const std::string& s) -> long long {
    std::unordered_map<int, long long> freq;
    int prefix = 0;
    long long result = 0;

    freq[0] = 1; // пустой префикс

    for (char c : s) {
        if (c == 'a') {
            prefix += 1;
        } else {
            prefix -= 1;
        }

        result += freq[prefix];
        freq[prefix]++;
    }

    return result;
}

auto main() -> int {
    int n;
    std::string s;

    std::cin >> n;
    std::cin >> s;

    std::cout << countBalancedSubsegments(s) << '\n';

    return 0;
}