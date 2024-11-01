#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) std::cin >> a;
    std::ranges::sort(arr);
    int right = n / 2;
    int left = right - 1;
    while (left >= 0) {
        if (n & 1) {
            std::cout << arr[right] << ' ' << arr[left] << ' ';
        } else {
            std::cout << arr[left] << ' ' << arr[right] << ' ';
        }
        left--, right++;
    }
    if (right < n) {
        std::cout << arr[right];
    }
}
