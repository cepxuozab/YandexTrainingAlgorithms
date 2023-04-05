#include <array>
#include <iostream>
#include <string>

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
    std::string s1, s2;
    std::cin >> s1 >> s2;
    std::array<int, 26> count1{}, count2{};
    for (char ch : s1) {
        count1[ch - 'a']++;
    }
    for (char ch : s2) {
        count2[ch - 'a']++;
    }
    int pos1 = 0, pos2 = 0;
    std::string ans;
    for (char ch = 'z'; ch >= 'a'; --ch) {
        while (count1[ch - 'a'] > 0 && count2[ch - 'a'] > 0) {
            ans.push_back(ch);
            while (s1[pos1] != ch) {
                count1[s1[pos1] - 'a']--;
                pos1++;
            }
            count1[s1[pos1] - 'a']--;
            pos1++;
            while (s2[pos2] != ch) {
                count2[s2[pos2] - 'a']--;
                pos2++;
            }
            count2[s2[pos2] - 'a']--;
            pos2++;
        }
    }
    std::cout << ans << '\n';
    return 0;
}
