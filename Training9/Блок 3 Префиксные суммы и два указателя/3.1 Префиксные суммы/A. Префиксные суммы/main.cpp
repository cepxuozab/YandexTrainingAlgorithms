#include <iostream>
#include <vector>
#include<numeric>

[[maybe_unused]] static auto const fastIO = []()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using Type = int64_t;

auto ReadVector(unsigned n) -> std::vector<Type>;

auto main() -> int
{
    unsigned n;
    std::cin >> n;
    auto numbers = ReadVector(n);
    std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());
    for (auto a : numbers)std::cout << a << ' ';
}

auto ReadVector(unsigned n) -> std::vector<Type>
{
    std::vector<Type> arr(n);
    for (auto& a : arr)
    {
        std::cin >> a;
    }
    return arr;
}
