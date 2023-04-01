#include <iostream>
#include <vector>

auto main() -> int
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (auto& a : arr) {
        std::cin >> a;
    }
    std::cout << arr[arr.size() / 2] << '\n';
    return 0;
}
