#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

auto const FASTIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    int n;
    std::cin >> n;
    puts("Initial array:");
    size_t mx = 0;
    std::map<char, std::vector<std::string>> dict;
    for (char ch = '0'; ch <= '9'; ++ch) {
        dict[ch] = {};
    }
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        if (i == n - 1) {
            puts(s.c_str());
        } else {
            printf("%s, ", s.c_str());
        }
        mx = s.length();
        dict[s.back()].push_back(s);
    }
    puts("**********");
    std::map<char, std::vector<std::string>> nd;
    for (size_t i = 0; i < mx; ++i) {
        for (char ch = '0'; ch <= '9'; ++ch) {
            nd[ch] = {};
        }
        printf("Phase %lld\n", i + 1);
        for (auto const& [_, str] : dict) {
            for (auto h : str) {
                nd[h[mx - i - 1]].push_back(h);
            }
        }
        dict.swap(nd);
        for (char j = '0'; j <= '9'; ++j) {
            printf("Bucket %c: ", j);
            auto const& bucket = dict[j];
            if (bucket.empty()) {
                puts("empty");
            } else {
                for (size_t u = 0; u < bucket.size(); ++u) {
                    if (u + 1 == bucket.size()) {
                        puts(bucket[u].c_str());
                    } else {
                        printf("%s, ", bucket[u].c_str());
                    }
                }
            }
        }
        puts("**********");
    }
    puts("Sorted array:");
    std::string res;
    for (auto const& [_, strs] : dict) {
        for (auto const& str : strs) {
            res.append(str + ", ");
        }
    }
    puts(res.substr(0, res.size() - 2).c_str());
}
