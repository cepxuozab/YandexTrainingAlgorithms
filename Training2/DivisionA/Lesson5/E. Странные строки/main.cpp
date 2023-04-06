#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include <iostream>

struct Pair {
    int len1;
    int len2;
};

auto countStrangeString(std::string_view s) -> int64_t
{
    std::vector<char> groupChar{ s[0] };
    std::vector<int> groupSize{ 1 };
    int const size = s.length();
    for (int i = 1; i < size; ++i) {
        if (s[i] == s[i - 1]) {
            groupSize.back()++;
        }
        else {
            groupChar.push_back(s[i]);
            groupSize.push_back(1);
        }
    }
    int maxsize[1 + 'z']{};
    for (int i = 0; i < (int)groupSize.size(); ++i) {
        int c = groupChar[i];
        maxsize[c] = std::max(maxsize[c], groupSize[i]);
    }

    int64_t ans = 0;
    for (int c = 'a'; c <= 'z'; ++c) {
        ans += maxsize[c];
    }
    std::vector<Pair> pairs[1 + 'z'][1 + 'z']{};
    for (int i = 1; i < (int)groupSize.size(); ++i) {
        int c1 = groupChar[i - 1];
        int c2 = groupChar[i];
        int len1 = groupSize[i - 1];
        int len2 = groupSize[i];
        pairs[c1][c2].push_back(Pair(len1, len2));
    }
    for (int c1 = 'a'; c1 <= 'z'; ++c1) {
        for (int c2 = 'a'; c2 <= 'z'; ++c2) {
            auto& p = pairs[c1][c2];
            if (p.empty()) {
                continue;
            }
            std::sort(p.begin(), p.end(),
                [](const Pair& left, const Pair& right) { return left.len1 != right.len1
                ? left.len1 > right.len1
                : left.len2 < right.len2; });
            ans += 1LL * p[0].len1 * p[0].len2;
            int maxlen2 = p[0].len2;
            for (int i = 1; i < (int)p.size(); ++i) {
                if (p[i].len2 > maxlen2) {
                    ans += 1LL * p[i].len1 * (p[i].len2 - maxlen2);
                    maxlen2 = p[i].len2;
                }
            }
        }
    }
    return ans;
}

auto main() -> int
{
    std::string str;
    std::cin >> str;
    std::cout << countStrangeString(str) << '\n';
}