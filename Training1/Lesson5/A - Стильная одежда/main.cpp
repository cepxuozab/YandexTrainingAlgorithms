#include <algorithm>
#include <iostream>
#include <vector>

using IVector = std::vector<int>;

auto Read(unsigned n) -> IVector;

auto FindNearesr(IVector const& lhs, IVector const& rhs) -> std::pair<int, int>;

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    unsigned n;
    std::cin >> n;
    IVector t_shirts = Read(n);
    unsigned m;
    std::cin >> m;
    IVector pants = Read(m);
    auto [shirt, pant] = FindNearesr(t_shirts, pants);
    std::cout << shirt << ' ' << pant << std::endl;
}

auto Read(unsigned n) -> IVector
{
    IVector arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    return arr;
}

auto FindNearesr(IVector const& lhs, IVector const& rhs) -> std::pair<int, int>
{
    int const n = (int)lhs.size();
    int const m = (int)rhs.size();
    int min_diff = abs(lhs[0] - rhs[0]);
    int left = 0;
    int right = 0;
    for (int i = 0, j = 0; i < n && j < m;) {
        if (min_diff > abs(lhs[i] - rhs[j])) {
            min_diff = abs(lhs[i] - rhs[j]);
            left = i;
            right = j;
        }
        if (lhs[i] < rhs[j]) {
            i += 1;
        } else {
            j += 1;
        }
    }
    return { lhs[left], rhs[right] };
}
