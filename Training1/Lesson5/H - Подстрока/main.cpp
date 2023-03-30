#include <array>
#include <iostream>
#include <string>
#include <string_view>

auto StringRepeats(std::string_view s, int k) -> std::pair<int, int>;

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    unsigned n, k;
    std::cin >> n >> k;
    std::string str;
    std::cin >> str;
    auto [maxlen, maxleft] = StringRepeats(str, k);
    std::cout << maxlen << ' ' << maxleft << std::endl;
}

auto StringRepeats(std::string_view s, int k) -> std::pair<int, int>
{
    int const n = (int)s.length();
    int tl = 0, tr = 0, grl = 0, grr = 0;
    int const ALPHABET = 26;
    std::array<int, ALPHABET> cntr {};
    while (tr < n) {
        if (cntr[s[tr] - 'a'] < k) {
            if (tr - tl > grr - grl) {
                grr = tr, grl = tl;
            }
            cntr[s[tr] - 'a'] += 1;
            tr += 1;
        } else {
            tl = tr - k + 1;
            cntr.fill(0);
        }
    }
    return { grr - grl + 1, grl + 1 };
}
