#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    if (!freopen("input.txt", "r", stdin)) {
        throw std::invalid_argument("can't read");
    }
    int n;
    int m;
    std::cin >> n >> m;
    std::string str;
    std::cin >> str;
    std::array<int, 26> dict{};
    for (char ch : str) {
        dict[ch - 'a']++;
    }
    std::unordered_map<char, std::string> maps;
    for (int i = 0; i < m; ++i) {
        std::string s;
        std::cin >> s;
        maps[s[0]].push_back(s[1]);
    }
    int64_t res = 0;
    for (char ch : str) {
        dict[ch - 'a']--;
        auto const& arr = maps[ch];

        for (char c : arr) {
            res += dict[c - 'a'];
        }
    }
    std::cout << res;
}
