#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using ull = unsigned long long;

struct RollingHash {
    ull base;
    std::vector<ull> pw, h;

    RollingHash(const std::string& s) : pw(s.size() + 1), h(s.size() + 1, 0) {
        std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        base = std::max(ull(256), static_cast<ull>(rng()) | 1);
        pw[0] = 1;
        for (size_t i = 0; i < s.size(); ++i) {
            pw[i + 1] = pw[i] * base;
            h[i + 1] = h[i] * base + static_cast<ull>(s[i] - 'a' + 1);
        }
    }

    [[nodiscard]] ull get(int l, int r) const {
        return h[r] - h[l] * pw[r - l];
    }
};

auto maxCharFrequency(const std::string& s) -> int {
    std::vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;
    return std::ranges::max(freq);
}

auto hasSubstringWithKNonOverlapping(const std::string& s, const RollingHash& rh, int len, int K) -> bool {
    int n = s.size();
    int cnt = n - len + 1;

    std::vector<std::pair<ull, int>> hashes(cnt);
    for (int i = 0; i < cnt; ++i)
        hashes[i] = {rh.get(i, i + len), i};
    std::ranges::sort(hashes);

    for (int i = 0; i < cnt; ) {
        int j = i;
        while (j < cnt && hashes[j].first == hashes[i].first) ++j;

        if (j - i >= K) {
            std::vector<int> positions;
            positions.reserve(j - i);
            for (int k = i; k < j; ++k)
                positions.push_back(hashes[k].second);
            std::ranges::sort(positions);

            int found = 0, last = -len;
            for (int pos : positions) {
                if (pos - last >= len) {
                    ++found;
                    last = pos;
                }
            }
            if (found >= K) return true;
        }
        i = j;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    if (!(std::cin >> s)) return 0;

    int K = maxCharFrequency(s);
    RollingHash rh(s);

    int low = 1, high = static_cast<int>(s.size()) / K, ans = 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (hasSubstringWithKNonOverlapping(s, rh, mid, K)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    std::cout << ans << "\n";
    return 0;
}