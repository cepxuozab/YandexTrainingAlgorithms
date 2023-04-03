#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

auto split(const std::string& text, char sep = ' ') -> std::set<int>
{
    std::set<int> tokens;
    std::size_t start = 0;
    std::size_t end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        if (end != start) {
            tokens.insert(stoi(text.substr(start, end - start)));
        }
        start = end + 1;
    }
    if (end != start) {
        tokens.insert(stoi(text.substr(start)));
    }
    return tokens;
}

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        throw std::invalid_argument("can't read");
    }

    int n;
    std::cin >> n;
    std::cin.ignore(INT_MAX, '\n');

    std::set<int> possible;
    for (int i = 1; i <= n; ++i) {
        possible.insert(i);
    }
    std::string ans;
    for (std::string line; getline(std::cin, line);) {
        if (line == "HELP") {
            break;
        }
        std::set<int> nums(split(line));
        std::set<int> intersect;
        std::set_intersection(possible.begin(), possible.end(),
            nums.begin(), nums.end(), std::inserter(intersect, intersect.end()));
        if (intersect.size() > possible.size() / 2) {
            ans += "YES\n";
            possible.swap(intersect);
        } else {
            ans += "NO\n";
            for (int x : nums) {
                possible.erase(x);
            }
        }
    }

    std::cout << ans;
    for (int i : possible) {
        std::cout << i << ' ';
    }

    return 0;
}
