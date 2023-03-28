#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

auto ReadVector() -> std::vector<int>;

auto NearestNumber(std::vector<int> const& arr, int target) -> int;

int main()
{
    freopen("input.txt", "r", stdin);
    auto const arr = ReadVector();
    int target;
    std::cin >> target;
    std::cout << NearestNumber(arr, target);
    return 0;
}

auto ReadVector() -> std::vector<int>
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) {
        std::cin >> a;
    }
    return arr;
}
auto NearestNumber(std::vector<int> const& arr, int target) -> int
{
    auto ans = std::ranges::min_element(arr, [target](int a, int b) { return abs(a - target) < abs(b - target); });
    return *ans;
}
