#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <vector>
auto Read(unsigned n) -> std::vector<uint8_t>;

void Print(std::vector<uint8_t> const& arr);

auto GetMinimumToAdded(std::vector<uint8_t> const& arr) -> std::vector<uint8_t>;

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    unsigned n;
    std::cin >> n;
    Print(GetMinimumToAdded(Read(n)));
}

auto Read(unsigned n) -> std::vector<uint8_t>
{
    std::vector<uint8_t> arr(n);
    for (auto& i : arr) {
        std::cin >> i;
    }
    return arr;
}

void Print(std::vector<uint8_t> const& arr)
{
    std::cout << arr.size() << '\n';
    for (auto elem : arr) {
        std::cout << elem << ' ';
    }
}

auto computeLPSArray(std::vector<uint8_t> const& s) -> std::vector<int>
{
    std::vector<int> p(s.size());
    for (size_t i = 1; i < s.size(); i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        j += static_cast<int>(s[i] == s[j]);
        p[i] = j;
    }
    return p;
}

auto GetMinimumToAdded(std::vector<uint8_t> const& arr) -> std::vector<uint8_t>
{
    std::vector<uint8_t> tmp(arr.rbegin(), arr.rend());
    tmp.push_back(UINT8_MAX);
    tmp.insert(tmp.end(), arr.begin(), arr.end());
    auto lsp = computeLPSArray(tmp);

    return { std::make_reverse_iterator((arr.begin() + (arr.size() - lsp.back()))), arr.rend() };
}
