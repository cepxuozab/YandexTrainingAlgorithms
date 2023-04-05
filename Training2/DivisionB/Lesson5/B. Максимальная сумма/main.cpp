#include <iostream>
#include <numeric>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using Type = int64_t;
auto ReadVector(unsigned n) -> std::vector<Type>;

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        throw std::invalid_argument("can't read");
    }
    if (freopen("output.txt", "w", stdout) == nullptr) {
        throw std::invalid_argument("can't write");
    }
    unsigned n;
    std::cin >> n;
    auto arr = ReadVector(n);
    Type ans = arr[0];
    Type sum = 0;
    for (unsigned r = 0; r < n; ++r) {
        sum += arr[r];
        ans = (ans > sum) ? ans : sum;
        sum = (sum > 0) ? sum : 0;
    }
    std::cout << ans << '\n';
}

auto ReadVector(unsigned n) -> std::vector<Type>
{
    std::vector<Type> arr(n);
    for (auto& a : arr) {
        std::cin >> a;
    }
    return arr;
}
