#include <iostream>
#include <cstdint>
#include <limits>
#include <vector>
#include <algorithm>


auto HalfReportLen(int w, std::vector<int> const& arr) -> int {
    int row_count = 1;
    int64_t row_len = 0;
    for (auto& word_len : arr) {
        if (word_len > w) {
            return std::numeric_limits<int>::max();
        }
        if (row_len + word_len <= w)
            row_len += word_len + 1;
        else {
            row_count += 1;
            row_len = word_len + 1;
        }
    }
    return row_count;
}

auto ReportLen(int half, int w, std::vector<int> const& arr_a, std::vector<int> const& arr_b) -> int {
    auto left = HalfReportLen(half, arr_a);
    auto right = HalfReportLen(w - half, arr_b);
    return std::max(left, right);
}


auto CheckLen(int half, int w, std::vector<int> const& arr_a, std::vector<int> const& arr_b) -> bool {
    auto left = HalfReportLen(half, arr_a);
    auto right = HalfReportLen(w - half, arr_b);
    return left <= right;
}

template<typename Func, typename...Types>
auto UpperBound(int l, int r, Func cmp, Types...types) {
    while (l < r) {
        auto mid = (l + r) / 2;
        if (cmp(mid, types...)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    if (!cmp(l, types...)) {
        l += 1;
    }
    return l;
}

auto Report(int w, std::vector<int> const& arr_a, std::vector<int> const& arr_b) -> int {
    auto l = std::ranges::max(arr_a);
    auto r = w - std::ranges::max(arr_b);
    if (l == r) {
        return ReportLen(l, w, arr_a, arr_b);
    }
    auto buf = UpperBound(l, w, CheckLen, w, arr_a, arr_b);
    auto ans1 = ReportLen(buf, w, arr_a, arr_b);
    auto ans2 = buf > l ? ReportLen(buf - 1, w, arr_a, arr_b) : ans1;
    auto ans3 = buf < r ? ReportLen(buf + 1, w, arr_a, arr_b) : ans1;
    return std::min({ ans1, ans2, ans3 });
}

auto main() -> int {
    int w, n, m;
    std::cin >> w >> n >> m;
    std::vector<int> arr_a(n), arr_b(m);
    for (int& i : arr_a)std::cin >> i;
    for (int& i : arr_b)std::cin >> i;
    std::cout << Report(w, arr_a, arr_b);
}
