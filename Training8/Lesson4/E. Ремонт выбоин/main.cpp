#include <algorithm>
#include <iostream>
#include <vector>


auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    long long k; // k can be up to 1e12
    std::cin >> n >> m >> k;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Step 1: Count how many routes cover each segment
    std::vector<long long> diff(n + 2, 0); // 1-indexed, so need n+2
    for (int i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        diff[l] += 1;
        diff[r + 1] -= 1;
    }

    std::vector<long long> cnt(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cnt[i] = cnt[i - 1] + diff[i];
    }

    // Step 2: Compute initial total discomfort
    long long total_discomfort = 0;
    for (int i = 0; i < n; ++i) {
        total_discomfort += a[i] * cnt[i + 1]; // a[i] corresponds to segment i+1
    }

    // Step 3: Create list of (cnt, a) for segments with a > 0
    std::vector<std::pair<long long, long long>> segments; // (cnt, a)
    for (int i = 0; i < n; ++i) {
        if (a[i] > 0) {
            segments.emplace_back(cnt[i + 1], a[i]);
        }
    }

    // Step 4: Sort by cnt descending
    std::ranges::sort(segments, std::greater<>(), &std::pair<long long, long long>::first);

    // Step 5: Greedily repair
    long long remaining = k;
    for (auto [c, holes]: segments) {
        if (remaining == 0) break;
        auto repair = std::min(remaining, holes);
        total_discomfort -= repair * c;
        remaining -= repair;
    }

    std::cout << total_discomfort << '\n';

    return 0;
}