#include <iostream>
#include <vector>
#include <numeric>
#include <cstdint>
#include <algorithm>

[[maybe_unused]] static auto const fastIO = []() -> std::nullptr_t
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using i64 = std::int64_t;

auto main() -> int
{
    constexpr i64 mod = 1'000'000'007;

    unsigned n;
    std::cin >> n;

    std::vector<i64> numbers(n);
    for (auto& a : numbers)
    {
        std::cin >> a;
    }

    std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());

    unsigned q;
    std::cin >> q;

    i64 x;
    std::cin >> x;

    i64 ans = 0;

    for (unsigned i = 0; i < q; ++i)
    {
        const i64 x0 = x;
        const i64 x1 = (11173 * x0 + 1) % mod;

        const auto left = std::min(x0 % n, x1 % n);
        const auto right = std::max(x0 % n, x1 % n);

        i64 range_sum = numbers[right];
        if (left != 0)
            range_sum -= numbers[left - 1];

        range_sum %= mod;
        if (range_sum < 0)
            range_sum += mod;

        ans += range_sum;
        ans %= mod;

        x = (11173 * x1 + 1) % mod;
    }

    std::cout << ans << "\n";

    return 0;
}
