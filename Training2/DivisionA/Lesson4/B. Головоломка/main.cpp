#include <algorithm>
#include <queue>
#include <iostream>
#include <string>
#include <array>

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
    std::array<int, 26> dict{};
    for (int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        for (char ch : str) {
            dict[ch - 'A']++;
        }
    }
    for (int i = 0; i < m; ++i) {
        std::string str;
        std::cin >> str;
        for (char ch : str) {
            dict[ch - 'A']--;
        }
    }
    //std::priority_queue<char, std::vector<char>, std::greater<>> pqueue;
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        int i = ch - 'A';
        for (int j = 0; j < dict[i]; ++j) {
            std::cout << ch;
        }
    }

    std::cout << '\n';

}
