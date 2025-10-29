#include <algorithm>
#include <iostream>
#include <vector>
#include <format>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    long long x;
    std::cin >> n >> m >> x;

    std::vector<std::pair<double, double>> intervals;

    for (int i = 0; i < n; ++i) {
        long long a, b, v;
        std::cin >> a >> b >> v;

        long long l0 = std::min(a, b);
        long long r0 = std::max(a, b);

        double t_start, t_end;

        if (a < b) {
            // moving right
            t_start = (double) (x - r0) / v;
            t_end = (double) (x - l0) / v;
        } else {
            // moving left
            t_start = (double) (l0 - x) / v;
            t_end = (double) (r0 - x) / v;
        }

        if (t_end < 0) continue;
        double start = std::max(0.0, t_start);
        if (start <= t_end) {
            intervals.emplace_back(start, t_end);
        }
    }

    // Merge intervals
    if (intervals.empty()) {
        // No trains ever occupy the crossing
        for (int i = 0; i < m; ++i) {
            long long t;
            std::cin >> t;
            std::cout << t << ".000000000\n";
        }
        return 0;
    }

    std::ranges::sort(intervals);
    std::vector<std::pair<double, double>> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        auto &last = merged.back();
        if (intervals[i].first <= last.second) {
            last.second = std::max(last.second, intervals[i].second);
        } else {
            merged.push_back(intervals[i]);
        }
    }

    // Process queries
    for (int i = 0; i < m; ++i) {
        long long t_input;
        std::cin >> t_input;
        auto t = (double) t_input;

        // Binary search: find the rightmost interval with .first <= t
        int lo = 0, hi = (int) merged.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (merged[mid].first <= t) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        // lo is first index with .first > t, so candidate is lo-1
        if (lo == 0) {
            std::cout << std::format("{:.9}\n", t);
            // t is before first interval

        } else {
            auto &interval = merged[lo - 1];
            if (t <= interval.second) {
                // t is inside the interval
                std::cout << std::format("{:.9}\n", interval.second);

            } else {
                std::cout << std::format("{:.9}\n", t);
            }
        }
    }

    return 0;
}