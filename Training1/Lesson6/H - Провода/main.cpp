#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

auto Read(unsigned n) -> std::vector<int64_t>;

auto calculate(std::vector<int64_t> const& arr, int len) -> int;

auto binarySearch(std::vector<int64_t> const& arr, int64_t amount) -> int64_t;

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    unsigned n;
    int64_t amount;
    std::cin >> n >> amount;
    std::cout << binarySearch(Read(n), amount) << '\n';
    return 0;
}
auto Read(unsigned n) -> std::vector<int64_t>
{
    std::vector<int64_t> arr(n);
    for (auto& i : arr) {
        std::cin >> i;
    }
    return arr;
}

auto calculate(std::vector<int64_t> const& arr, int len) -> int
{
    return std::accumulate(arr.begin(), arr.end(), 0LL,
        [len](auto l, auto r) { return l + r / len; });
}

auto binarySearch(std::vector<int64_t> const& arr, int64_t amount) -> int64_t
{
    int64_t left = 0;
    int64_t right = *std::max_element(arr.begin(), arr.end());
    int64_t len = 0;
    while (left <= right) {
        int64_t m = (left + right) >> 1;
        if (m == 0) {
            left = m + 1;
            continue;
        }
        int64_t curAmount = calculate(arr, m);
        if (curAmount < amount)
            right = m - 1;
        else if (curAmount >= amount) {
            left = m + 1;
            len = (len > m) ? len : m;
        }
    }
    return len;
}
